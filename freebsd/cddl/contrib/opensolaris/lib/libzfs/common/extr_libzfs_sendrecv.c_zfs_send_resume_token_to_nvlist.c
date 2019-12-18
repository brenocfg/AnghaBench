#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long long* zc_word; } ;
typedef  TYPE_1__ zio_cksum_t ;
typedef  unsigned long long uLongf ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 unsigned int ZFS_SEND_RESUME_TOKEN_VERSION ; 
 scalar_t__ Z_OK ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fletcher_4_native (unsigned char*,int,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int nvlist_unpack (void*,unsigned long long,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int sscanf (char const*,char*,...) ; 
 int strlen (char const*) ; 
 char* strrchr (char const*,char) ; 
 scalar_t__ uncompress (void*,unsigned long long*,unsigned char*,int) ; 
 void* zfs_alloc (int /*<<< orphan*/ *,unsigned long long) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 

nvlist_t *
zfs_send_resume_token_to_nvlist(libzfs_handle_t *hdl, const char *token)
{
	unsigned int version;
	int nread;
	unsigned long long checksum, packed_len;

	/*
	 * Decode token header, which is:
	 *   <token version>-<checksum of payload>-<uncompressed payload length>
	 * Note that the only supported token version is 1.
	 */
	nread = sscanf(token, "%u-%llx-%llx-",
	    &version, &checksum, &packed_len);
	if (nread != 3) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "resume token is corrupt (invalid format)"));
		return (NULL);
	}

	if (version != ZFS_SEND_RESUME_TOKEN_VERSION) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "resume token is corrupt (invalid version %u)"),
		    version);
		return (NULL);
	}

	/* convert hexadecimal representation to binary */
	token = strrchr(token, '-') + 1;
	int len = strlen(token) / 2;
	unsigned char *compressed = zfs_alloc(hdl, len);
	for (int i = 0; i < len; i++) {
		nread = sscanf(token + i * 2, "%2hhx", compressed + i);
		if (nread != 1) {
			free(compressed);
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "resume token is corrupt "
			    "(payload is not hex-encoded)"));
			return (NULL);
		}
	}

	/* verify checksum */
	zio_cksum_t cksum;
	fletcher_4_native(compressed, len, NULL, &cksum);
	if (cksum.zc_word[0] != checksum) {
		free(compressed);
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "resume token is corrupt (incorrect checksum)"));
		return (NULL);
	}

	/* uncompress */
	void *packed = zfs_alloc(hdl, packed_len);
	uLongf packed_len_long = packed_len;
	if (uncompress(packed, &packed_len_long, compressed, len) != Z_OK ||
	    packed_len_long != packed_len) {
		free(packed);
		free(compressed);
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "resume token is corrupt (decompression failed)"));
		return (NULL);
	}

	/* unpack nvlist */
	nvlist_t *nv;
	int error = nvlist_unpack(packed, packed_len, &nv, KM_SLEEP);
	free(packed);
	free(compressed);
	if (error != 0) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "resume token is corrupt (nvlist_unpack failed)"));
		return (NULL);
	}
	return (nv);
}