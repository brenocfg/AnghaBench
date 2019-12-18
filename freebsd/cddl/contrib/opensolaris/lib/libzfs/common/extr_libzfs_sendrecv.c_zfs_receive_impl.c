#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ zio_cksum_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct drr_begin {scalar_t__ drr_magic; scalar_t__ drr_versioninfo; scalar_t__ drr_creation_time; scalar_t__ drr_type; scalar_t__ drr_flags; scalar_t__ drr_toguid; scalar_t__ drr_fromguid; char* drr_toname; } ;
struct TYPE_19__ {int /*<<< orphan*/  byteswap; scalar_t__ isprefix; } ;
typedef  TYPE_3__ recvflags_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  nonpackage_sendfs ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  errbuf ;
typedef  int /*<<< orphan*/  drr ;
struct TYPE_17__ {struct drr_begin drr_begin; } ;
struct TYPE_20__ {scalar_t__ drr_type; scalar_t__ drr_payloadlen; TYPE_1__ drr_u; } ;
typedef  TYPE_4__ dmu_replay_record_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;

/* Variables and functions */
 scalar_t__ BSWAP_32 (scalar_t__) ; 
 scalar_t__ BSWAP_64 (scalar_t__) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ DMU_BACKUP_MAGIC ; 
 int DMU_COMPOUNDSTREAM ; 
 int /*<<< orphan*/  DMU_GET_FEATUREFLAGS (scalar_t__) ; 
 int DMU_GET_STREAM_HDRTYPE (scalar_t__) ; 
 int /*<<< orphan*/  DMU_STREAM_SUPPORTED (int /*<<< orphan*/ ) ; 
 int DMU_SUBSTREAM ; 
 scalar_t__ DRR_BEGIN ; 
 scalar_t__ DRR_END ; 
 int ENODATA ; 
 int /*<<< orphan*/  EZFS_BADSTREAM ; 
 int /*<<< orphan*/  EZFS_NOENT ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  ZFS_TYPE_DATASET ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fletcher_4_incremental_byteswap (TYPE_4__*,int,TYPE_2__*) ; 
 int recv_read (int /*<<< orphan*/ *,int,TYPE_4__*,int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  zfs_dataset_exists (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,char*,...) ; 
 int zfs_receive_one (int /*<<< orphan*/ *,int,char const*,char const*,TYPE_3__*,TYPE_4__*,TYPE_4__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**,int,int /*<<< orphan*/ *,char const*) ; 
 int zfs_receive_package (int /*<<< orphan*/ *,int,char const*,TYPE_3__*,TYPE_4__*,TYPE_2__*,char**,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_receive_impl(libzfs_handle_t *hdl, const char *tosnap,
    const char *originsnap, recvflags_t *flags, int infd, const char *sendfs,
    nvlist_t *stream_nv, avl_tree_t *stream_avl, char **top_zfs, int cleanup_fd,
    uint64_t *action_handlep, const char *finalsnap)
{
	int err;
	dmu_replay_record_t drr, drr_noswap;
	struct drr_begin *drrb = &drr.drr_u.drr_begin;
	char errbuf[1024];
	zio_cksum_t zcksum = { 0 };
	uint64_t featureflags;
	int hdrtype;

	(void) snprintf(errbuf, sizeof (errbuf), dgettext(TEXT_DOMAIN,
	    "cannot receive"));

	if (flags->isprefix &&
	    !zfs_dataset_exists(hdl, tosnap, ZFS_TYPE_DATASET)) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN, "specified fs "
		    "(%s) does not exist"), tosnap);
		return (zfs_error(hdl, EZFS_NOENT, errbuf));
	}
	if (originsnap &&
	    !zfs_dataset_exists(hdl, originsnap, ZFS_TYPE_DATASET)) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN, "specified origin fs "
		    "(%s) does not exist"), originsnap);
		return (zfs_error(hdl, EZFS_NOENT, errbuf));
	}

	/* read in the BEGIN record */
	if (0 != (err = recv_read(hdl, infd, &drr, sizeof (drr), B_FALSE,
	    &zcksum)))
		return (err);

	if (drr.drr_type == DRR_END || drr.drr_type == BSWAP_32(DRR_END)) {
		/* It's the double end record at the end of a package */
		return (ENODATA);
	}

	/* the kernel needs the non-byteswapped begin record */
	drr_noswap = drr;

	flags->byteswap = B_FALSE;
	if (drrb->drr_magic == BSWAP_64(DMU_BACKUP_MAGIC)) {
		/*
		 * We computed the checksum in the wrong byteorder in
		 * recv_read() above; do it again correctly.
		 */
		bzero(&zcksum, sizeof (zio_cksum_t));
		(void) fletcher_4_incremental_byteswap(&drr,
		    sizeof (drr), &zcksum);
		flags->byteswap = B_TRUE;

		drr.drr_type = BSWAP_32(drr.drr_type);
		drr.drr_payloadlen = BSWAP_32(drr.drr_payloadlen);
		drrb->drr_magic = BSWAP_64(drrb->drr_magic);
		drrb->drr_versioninfo = BSWAP_64(drrb->drr_versioninfo);
		drrb->drr_creation_time = BSWAP_64(drrb->drr_creation_time);
		drrb->drr_type = BSWAP_32(drrb->drr_type);
		drrb->drr_flags = BSWAP_32(drrb->drr_flags);
		drrb->drr_toguid = BSWAP_64(drrb->drr_toguid);
		drrb->drr_fromguid = BSWAP_64(drrb->drr_fromguid);
	}

	if (drrb->drr_magic != DMU_BACKUP_MAGIC || drr.drr_type != DRR_BEGIN) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN, "invalid "
		    "stream (bad magic number)"));
		return (zfs_error(hdl, EZFS_BADSTREAM, errbuf));
	}

	featureflags = DMU_GET_FEATUREFLAGS(drrb->drr_versioninfo);
	hdrtype = DMU_GET_STREAM_HDRTYPE(drrb->drr_versioninfo);

	if (!DMU_STREAM_SUPPORTED(featureflags) ||
	    (hdrtype != DMU_SUBSTREAM && hdrtype != DMU_COMPOUNDSTREAM)) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "stream has unsupported feature, feature flags = %lx"),
		    featureflags);
		return (zfs_error(hdl, EZFS_BADSTREAM, errbuf));
	}

	if (strchr(drrb->drr_toname, '@') == NULL) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN, "invalid "
		    "stream (bad snapshot name)"));
		return (zfs_error(hdl, EZFS_BADSTREAM, errbuf));
	}

	if (DMU_GET_STREAM_HDRTYPE(drrb->drr_versioninfo) == DMU_SUBSTREAM) {
		char nonpackage_sendfs[ZFS_MAX_DATASET_NAME_LEN];
		if (sendfs == NULL) {
			/*
			 * We were not called from zfs_receive_package(). Get
			 * the fs specified by 'zfs send'.
			 */
			char *cp;
			(void) strlcpy(nonpackage_sendfs,
			    drr.drr_u.drr_begin.drr_toname,
			    sizeof (nonpackage_sendfs));
			if ((cp = strchr(nonpackage_sendfs, '@')) != NULL)
				*cp = '\0';
			sendfs = nonpackage_sendfs;
			VERIFY(finalsnap == NULL);
		}
		return (zfs_receive_one(hdl, infd, tosnap, originsnap, flags,
		    &drr, &drr_noswap, sendfs, stream_nv, stream_avl, top_zfs,
		    cleanup_fd, action_handlep, finalsnap));
	} else {
		assert(DMU_GET_STREAM_HDRTYPE(drrb->drr_versioninfo) ==
		    DMU_COMPOUNDSTREAM);
		return (zfs_receive_package(hdl, infd, tosnap, flags, &drr,
		    &zcksum, top_zfs, cleanup_fd, action_handlep));
	}
}