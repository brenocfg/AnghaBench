#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zio_cksum_t ;
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  tofs ;
struct drr_begin {scalar_t__ drr_magic; char* drr_toname; int /*<<< orphan*/  drr_versioninfo; } ;
typedef  int /*<<< orphan*/  sendfs ;
struct TYPE_14__ {int /*<<< orphan*/  nomount; int /*<<< orphan*/  dryrun; scalar_t__ istail; scalar_t__ isprefix; int /*<<< orphan*/  byteswap; } ;
typedef  TYPE_3__ recvflags_t ;
typedef  int /*<<< orphan*/  prop_changelist_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  errbuf ;
typedef  int /*<<< orphan*/  drre ;
struct TYPE_11__ {void** zc_word; } ;
struct TYPE_12__ {TYPE_10__ drr_checksum; } ;
struct TYPE_13__ {struct drr_begin drr_begin; TYPE_1__ drr_end; } ;
struct TYPE_15__ {scalar_t__ drr_type; scalar_t__ drr_payloadlen; TYPE_2__ drr_u; } ;
typedef  TYPE_4__ dmu_replay_record_t ;
typedef  int boolean_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;

/* Variables and functions */
 scalar_t__ BSWAP_32 (scalar_t__) ; 
 void* BSWAP_64 (void*) ; 
 int B_FALSE ; 
 scalar_t__ DMU_BACKUP_MAGIC ; 
 scalar_t__ DMU_COMPOUNDSTREAM ; 
 scalar_t__ DMU_GET_STREAM_HDRTYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ DRR_BEGIN ; 
 scalar_t__ DRR_END ; 
 int ENODATA ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  EZFS_BADSTREAM ; 
 int /*<<< orphan*/  EZFS_NOMEM ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  ZFS_PROP_MOUNTPOINT ; 
 int /*<<< orphan*/  ZFS_TYPE_FILESYSTEM ; 
 int /*<<< orphan*/  ZIO_CHECKSUM_EQUAL (TYPE_10__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  changelist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * changelist_gather (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int changelist_prefix (int /*<<< orphan*/ *) ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * fsavl_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsavl_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_boolean (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nvlist_lookup_string (int /*<<< orphan*/ *,char*,char**) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_name (int /*<<< orphan*/ *) ; 
 int recv_incremental_replication (int /*<<< orphan*/ *,char*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int recv_read (int /*<<< orphan*/ *,int,TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int recv_read_nvlist (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 
 char* strchr (char const*,char) ; 
 int strcspn (char*,char*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zfs_receive_impl (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,TYPE_3__*,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**,int,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
zfs_receive_package(libzfs_handle_t *hdl, int fd, const char *destname,
    recvflags_t *flags, dmu_replay_record_t *drr, zio_cksum_t *zc,
    char **top_zfs, int cleanup_fd, uint64_t *action_handlep)
{
	nvlist_t *stream_nv = NULL;
	avl_tree_t *stream_avl = NULL;
	char *fromsnap = NULL;
	char *sendsnap = NULL;
	char *cp;
	char tofs[ZFS_MAX_DATASET_NAME_LEN];
	char sendfs[ZFS_MAX_DATASET_NAME_LEN];
	char errbuf[1024];
	dmu_replay_record_t drre;
	int error;
	boolean_t anyerr = B_FALSE;
	boolean_t softerr = B_FALSE;
	boolean_t recursive;

	(void) snprintf(errbuf, sizeof (errbuf), dgettext(TEXT_DOMAIN,
	    "cannot receive"));

	assert(drr->drr_type == DRR_BEGIN);
	assert(drr->drr_u.drr_begin.drr_magic == DMU_BACKUP_MAGIC);
	assert(DMU_GET_STREAM_HDRTYPE(drr->drr_u.drr_begin.drr_versioninfo) ==
	    DMU_COMPOUNDSTREAM);

	/*
	 * Read in the nvlist from the stream.
	 */
	if (drr->drr_payloadlen != 0) {
		error = recv_read_nvlist(hdl, fd, drr->drr_payloadlen,
		    &stream_nv, flags->byteswap, zc);
		if (error) {
			error = zfs_error(hdl, EZFS_BADSTREAM, errbuf);
			goto out;
		}
	}

	recursive = (nvlist_lookup_boolean(stream_nv, "not_recursive") ==
	    ENOENT);

	if (recursive && strchr(destname, '@')) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "cannot specify snapshot name for multi-snapshot stream"));
		error = zfs_error(hdl, EZFS_BADSTREAM, errbuf);
		goto out;
	}

	/*
	 * Read in the end record and verify checksum.
	 */
	if (0 != (error = recv_read(hdl, fd, &drre, sizeof (drre),
	    flags->byteswap, NULL)))
		goto out;
	if (flags->byteswap) {
		drre.drr_type = BSWAP_32(drre.drr_type);
		drre.drr_u.drr_end.drr_checksum.zc_word[0] =
		    BSWAP_64(drre.drr_u.drr_end.drr_checksum.zc_word[0]);
		drre.drr_u.drr_end.drr_checksum.zc_word[1] =
		    BSWAP_64(drre.drr_u.drr_end.drr_checksum.zc_word[1]);
		drre.drr_u.drr_end.drr_checksum.zc_word[2] =
		    BSWAP_64(drre.drr_u.drr_end.drr_checksum.zc_word[2]);
		drre.drr_u.drr_end.drr_checksum.zc_word[3] =
		    BSWAP_64(drre.drr_u.drr_end.drr_checksum.zc_word[3]);
	}
	if (drre.drr_type != DRR_END) {
		error = zfs_error(hdl, EZFS_BADSTREAM, errbuf);
		goto out;
	}
	if (!ZIO_CHECKSUM_EQUAL(drre.drr_u.drr_end.drr_checksum, *zc)) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "incorrect header checksum"));
		error = zfs_error(hdl, EZFS_BADSTREAM, errbuf);
		goto out;
	}

	(void) nvlist_lookup_string(stream_nv, "fromsnap", &fromsnap);

	if (drr->drr_payloadlen != 0) {
		nvlist_t *stream_fss;

		VERIFY(0 == nvlist_lookup_nvlist(stream_nv, "fss",
		    &stream_fss));
		if ((stream_avl = fsavl_create(stream_fss)) == NULL) {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "couldn't allocate avl tree"));
			error = zfs_error(hdl, EZFS_NOMEM, errbuf);
			goto out;
		}

		if (fromsnap != NULL && recursive) {
			nvlist_t *renamed = NULL;
			nvpair_t *pair = NULL;

			(void) strlcpy(tofs, destname, sizeof (tofs));
			if (flags->isprefix) {
				struct drr_begin *drrb = &drr->drr_u.drr_begin;
				int i;

				if (flags->istail) {
					cp = strrchr(drrb->drr_toname, '/');
					if (cp == NULL) {
						(void) strlcat(tofs, "/",
						    sizeof (tofs));
						i = 0;
					} else {
						i = (cp - drrb->drr_toname);
					}
				} else {
					i = strcspn(drrb->drr_toname, "/@");
				}
				/* zfs_receive_one() will create_parents() */
				(void) strlcat(tofs, &drrb->drr_toname[i],
				    sizeof (tofs));
				*strchr(tofs, '@') = '\0';
			}

			if (!flags->dryrun && !flags->nomount) {
				VERIFY(0 == nvlist_alloc(&renamed,
				    NV_UNIQUE_NAME, 0));
			}

			softerr = recv_incremental_replication(hdl, tofs, flags,
			    stream_nv, stream_avl, renamed);

			/* Unmount renamed filesystems before receiving. */
			while ((pair = nvlist_next_nvpair(renamed,
			    pair)) != NULL) {
				zfs_handle_t *zhp;
				prop_changelist_t *clp = NULL;

				zhp = zfs_open(hdl, nvpair_name(pair),
				    ZFS_TYPE_FILESYSTEM);
				if (zhp != NULL) {
					clp = changelist_gather(zhp,
					    ZFS_PROP_MOUNTPOINT, 0, 0);
					zfs_close(zhp);
					if (clp != NULL) {
						softerr |=
						    changelist_prefix(clp);
						changelist_free(clp);
					}
				}
			}

			nvlist_free(renamed);
		}
	}

	/*
	 * Get the fs specified by the first path in the stream (the top level
	 * specified by 'zfs send') and pass it to each invocation of
	 * zfs_receive_one().
	 */
	(void) strlcpy(sendfs, drr->drr_u.drr_begin.drr_toname,
	    sizeof (sendfs));
	if ((cp = strchr(sendfs, '@')) != NULL) {
		*cp = '\0';
		/*
		 * Find the "sendsnap", the final snapshot in a replication
		 * stream.  zfs_receive_one() handles certain errors
		 * differently, depending on if the contained stream is the
		 * last one or not.
		 */
		sendsnap = (cp + 1);
	}

	/* Finally, receive each contained stream */
	do {
		/*
		 * we should figure out if it has a recoverable
		 * error, in which case do a recv_skip() and drive on.
		 * Note, if we fail due to already having this guid,
		 * zfs_receive_one() will take care of it (ie,
		 * recv_skip() and return 0).
		 */
		error = zfs_receive_impl(hdl, destname, NULL, flags, fd,
		    sendfs, stream_nv, stream_avl, top_zfs, cleanup_fd,
		    action_handlep, sendsnap);
		if (error == ENODATA) {
			error = 0;
			break;
		}
		anyerr |= error;
	} while (error == 0);

	if (drr->drr_payloadlen != 0 && recursive && fromsnap != NULL) {
		/*
		 * Now that we have the fs's they sent us, try the
		 * renames again.
		 */
		softerr = recv_incremental_replication(hdl, tofs, flags,
		    stream_nv, stream_avl, NULL);
	}

out:
	fsavl_destroy(stream_avl);
	nvlist_free(stream_nv);
	if (softerr)
		error = -2;
	if (anyerr)
		error = -1;
	return (error);
}