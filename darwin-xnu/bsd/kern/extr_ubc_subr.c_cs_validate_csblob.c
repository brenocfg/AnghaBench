#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_13__ {int type; int offset; } ;
struct TYPE_12__ {int hashType; int flags; } ;
struct TYPE_11__ {int length; int magic; } ;
struct TYPE_10__ {int count; TYPE_4__* index; } ;
typedef  TYPE_1__ CS_SuperBlob ;
typedef  TYPE_2__ CS_GenericBlob ;
typedef  TYPE_3__ CS_CodeDirectory ;
typedef  TYPE_4__ CS_BlobIndex ;

/* Variables and functions */
 size_t CSMAGIC_CODEDIRECTORY ; 
 size_t CSMAGIC_EMBEDDED_ENTITLEMENTS ; 
 size_t CSMAGIC_EMBEDDED_SIGNATURE ; 
 size_t CSSLOT_ALTERNATE_CODEDIRECTORIES ; 
 size_t CSSLOT_ALTERNATE_CODEDIRECTORY_LIMIT ; 
 size_t CSSLOT_CODEDIRECTORY ; 
 size_t CSSLOT_ENTITLEMENTS ; 
 size_t CS_ADHOC ; 
 scalar_t__ CS_HASHTYPE_SHA1 ; 
 int EBADEXEC ; 
 int cs_debug ; 
 int cs_validate_blob (TYPE_2__ const*,size_t) ; 
 int cs_validate_codedirectory (TYPE_3__ const*,size_t) ; 
 unsigned int hash_rank (TYPE_3__ const*) ; 
 size_t ntohl (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
cs_validate_csblob(
	const uint8_t *addr,
	const size_t blob_size,
	const CS_CodeDirectory **rcd,
	const CS_GenericBlob **rentitlements)
{
	const CS_GenericBlob *blob;
	int error;
	size_t length;

	*rcd = NULL;
	*rentitlements = NULL;

	blob = (const CS_GenericBlob *)(const void *)addr;

	length = blob_size;
	error = cs_validate_blob(blob, length);
	if (error)
		return error;
	length = ntohl(blob->length);

	if (ntohl(blob->magic) == CSMAGIC_EMBEDDED_SIGNATURE) {
		const CS_SuperBlob *sb;
		uint32_t n, count;
		const CS_CodeDirectory *best_cd = NULL;
		unsigned int best_rank = 0;
#if PLATFORM_WatchOS
		const CS_CodeDirectory *sha1_cd = NULL;
#endif

		if (length < sizeof(CS_SuperBlob))
			return EBADEXEC;

		sb = (const CS_SuperBlob *)blob;
		count = ntohl(sb->count);

		/* check that the array of BlobIndex fits in the rest of the data */
		if ((length - sizeof(CS_SuperBlob)) / sizeof(CS_BlobIndex) < count)
			return EBADEXEC;

		/* now check each BlobIndex */
		for (n = 0; n < count; n++) {
			const CS_BlobIndex *blobIndex = &sb->index[n];
			uint32_t type = ntohl(blobIndex->type);
			uint32_t offset = ntohl(blobIndex->offset);
			if (length < offset)
				return EBADEXEC;

			const CS_GenericBlob *subBlob =
				(const CS_GenericBlob *)(const void *)(addr + offset);

			size_t subLength = length - offset;

			if ((error = cs_validate_blob(subBlob, subLength)) != 0)
				return error;
			subLength = ntohl(subBlob->length);

			/* extra validation for CDs, that is also returned */
			if (type == CSSLOT_CODEDIRECTORY || (type >= CSSLOT_ALTERNATE_CODEDIRECTORIES && type < CSSLOT_ALTERNATE_CODEDIRECTORY_LIMIT)) {
				const CS_CodeDirectory *candidate = (const CS_CodeDirectory *)subBlob;
				if ((error = cs_validate_codedirectory(candidate, subLength)) != 0)
					return error;
				unsigned int rank = hash_rank(candidate);
				if (cs_debug > 3)
					printf("CodeDirectory type %d rank %d at slot 0x%x index %d\n", candidate->hashType, (int)rank, (int)type, (int)n);
				if (best_cd == NULL || rank > best_rank) {
					best_cd = candidate;
					best_rank = rank;

					if (cs_debug > 2)
						printf("using CodeDirectory type %d (rank %d)\n", (int)best_cd->hashType, best_rank);
					*rcd = best_cd;
				} else if (best_cd != NULL && rank == best_rank) {
					/* repeat of a hash type (1:1 mapped to ranks), illegal and suspicious */
					printf("multiple hash=%d CodeDirectories in signature; rejecting\n", best_cd->hashType);
					return EBADEXEC;
				}
#if PLATFORM_WatchOS
				if (candidate->hashType == CS_HASHTYPE_SHA1) {
					if (sha1_cd != NULL) {
						printf("multiple sha1 CodeDirectories in signature; rejecting\n");
						return EBADEXEC;
					}
					sha1_cd = candidate;
				}
#endif
			} else if (type == CSSLOT_ENTITLEMENTS) {
				if (ntohl(subBlob->magic) != CSMAGIC_EMBEDDED_ENTITLEMENTS) {
					return EBADEXEC;
				}
				if (*rentitlements != NULL) {
					printf("multiple entitlements blobs\n");
					return EBADEXEC;
				}
				*rentitlements = subBlob;
			}
		}

#if PLATFORM_WatchOS
		/* To keep watchOS fast enough, we have to resort to sha1 for
		 * some code.
		 *
		 * At the time of writing this comment, known sha1 attacks are
		 * collision attacks (not preimage or second preimage
		 * attacks), which do not apply to platform binaries since
		 * they have a fixed hash in the trust cache.  Given this
		 * property, we only prefer sha1 code directories for adhoc
		 * signatures, which always have to be in a trust cache to be
		 * valid (can-load-cdhash does not exist for watchOS). Those
		 * are, incidentally, also the platform binaries, for which we
		 * care about the performance hit that sha256 would bring us.
		 *
		 * Platform binaries may still contain a (not chosen) sha256
		 * code directory, which keeps software updates that switch to
		 * sha256-only small.
		 */

		if (*rcd != NULL && sha1_cd != NULL && (ntohl(sha1_cd->flags) & CS_ADHOC)) {
			if (sha1_cd->flags != (*rcd)->flags) {
				printf("mismatched flags between hash %d (flags: %#x) and sha1 (flags: %#x) cd.\n",
					   (int)(*rcd)->hashType, (*rcd)->flags, sha1_cd->flags);
				*rcd = NULL;
				return EBADEXEC;
			}

			*rcd = sha1_cd;
		}
#endif

	} else if (ntohl(blob->magic) == CSMAGIC_CODEDIRECTORY) {

		if ((error = cs_validate_codedirectory((const CS_CodeDirectory *)(const void *)addr, length)) != 0)
			return error;
		*rcd = (const CS_CodeDirectory *)blob;
	} else {
		return EBADEXEC;
	}

	if (*rcd == NULL)
		return EBADEXEC;

	return 0;
}