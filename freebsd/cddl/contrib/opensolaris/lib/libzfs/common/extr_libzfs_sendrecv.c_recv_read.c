#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zio_cksum_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  EZFS_BADSTREAM ; 
 int SPA_MAXBLOCKSIZE ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fletcher_4_incremental_byteswap (void*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fletcher_4_incremental_native (void*,int,int /*<<< orphan*/ *) ; 
 int read (int,char*,int) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
recv_read(libzfs_handle_t *hdl, int fd, void *buf, int ilen,
    boolean_t byteswap, zio_cksum_t *zc)
{
	char *cp = buf;
	int rv;
	int len = ilen;

	assert(ilen <= SPA_MAXBLOCKSIZE);

	do {
		rv = read(fd, cp, len);
		cp += rv;
		len -= rv;
	} while (rv > 0);

	if (rv < 0 || len != 0) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "failed to read from stream"));
		return (zfs_error(hdl, EZFS_BADSTREAM, dgettext(TEXT_DOMAIN,
		    "cannot receive")));
	}

	if (zc) {
		if (byteswap)
			(void) fletcher_4_incremental_byteswap(buf, ilen, zc);
		else
			(void) fletcher_4_incremental_native(buf, ilen, zc);
	}
	return (0);
}