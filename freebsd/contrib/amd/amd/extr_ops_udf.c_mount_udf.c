#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  voidp ;
typedef  scalar_t__ uid_t ;
struct TYPE_7__ {char* fspec; int /*<<< orphan*/  version; void* sessionnr; void* gmtoff; scalar_t__ anon_gid; scalar_t__ anon_uid; scalar_t__ nobody_gid; scalar_t__ nobody_uid; int /*<<< orphan*/  udfmflags; } ;
typedef  TYPE_1__ udf_args_t ;
typedef  int /*<<< orphan*/  udf_args ;
struct TYPE_8__ {char* mnt_dir; char* mnt_fsname; char* mnt_opts; int /*<<< orphan*/  mnt_type; } ;
typedef  TYPE_2__ mntent_t ;
typedef  int /*<<< orphan*/  mnt ;
typedef  scalar_t__ gid_t ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  MTYPE_TYPE ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  MNT2_UDF_OPT_CLOSESESSION ; 
 int /*<<< orphan*/  MNTTAB_OPT_CLOSESESSION ; 
 char* MNTTAB_OPT_GMTOFF ; 
 char* MNTTAB_OPT_GROUP ; 
 char* MNTTAB_OPT_SESSIONNR ; 
 char* MNTTAB_OPT_USER ; 
 int /*<<< orphan*/  MNTTAB_TYPE_UDF ; 
 int /*<<< orphan*/  MOUNT_TYPE_UDF ; 
 int /*<<< orphan*/  UDFMNT_VERSION ; 
 int /*<<< orphan*/  XFREE (char*) ; 
 int /*<<< orphan*/  XLOG_ERROR ; 
 scalar_t__ a_gid (char*,char*) ; 
 void* a_num (char*,char*) ; 
 scalar_t__ a_uid (char*,char*) ; 
 scalar_t__ amu_hasmntopt (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int compute_mount_flags (TYPE_2__*) ; 
 char* hasmntstr (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mnttab_file_name ; 
 int mount_fs (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
mount_udf(char *mntdir, char *fs_name, char *opts, int on_autofs)
{
	udf_args_t udf_args;
	mntent_t mnt;
	int flags;
	char *str;
#if defined(HAVE_UDF_ARGS_T_NOBODY_UID) || defined(HAVE_UDF_ARGS_T_ANON_UID)
	uid_t uid_nobody;
	gid_t gid_nobody;
#endif /* defined(HAVE_UDF_ARGS_T_NOBODY_UID) || defined(HAVE_UDF_ARGS_T_ANON_UID) */
	/*
	 * Figure out the name of the file system type.
	 */
	MTYPE_TYPE type = MOUNT_TYPE_UDF;

#if defined(HAVE_UDF_ARGS_T_NOBODY_UID) || defined(HAVE_UDF_ARGS_T_ANON_UID)
	uid_nobody = a_uid("nobody", "user");
	if (uid_nobody == 0) {
		plog(XLOG_ERROR, "mount_udf: invalid uid for nobody");
		return EPERM;
	}
#endif /* defined(HAVE_UDF_ARGS_T_NOBODY_UID) || defined(HAVE_UDF_ARGS_T_ANON_UID) */

#if defined(HAVE_UDF_ARGS_T_NOBODY_GID) || defined(HAVE_UDF_ARGS_T_ANON_GID)
	gid_nobody = a_gid("nobody", "group");
	if (gid_nobody == 0) {
		plog(XLOG_ERROR, "mount_udf: invalid gid for nobody");
		return EPERM;
	}
#endif /* defined(HAVE_UDF_ARGS_T_NOBODY_GID) || defined(HAVE_UDF_ARGS_T_ANON_GID) */

	str = NULL;
	memset((voidp) &udf_args, 0, sizeof(udf_args)); /* Paranoid */

	/*
	 * Fill in the mount structure
	 */
	memset((voidp)&mnt, 0, sizeof(mnt));
	mnt.mnt_dir = mntdir;
	mnt.mnt_fsname = fs_name;
	mnt.mnt_type = MNTTAB_TYPE_UDF;
	mnt.mnt_opts = opts;

	flags = compute_mount_flags(&mnt);

#ifdef HAVE_UDF_ARGS_T_UDFMFLAGS
# if defined(MNT2_UDF_OPT_CLOSESESSION) && defined(MNTTAB_OPT_CLOSESESSION)
	if (amu_hasmntopt(&mnt, MNTTAB_OPT_CLOSESESSION))
		udf_args.udfmflags |= MNT2_UDF_OPT_CLOSESESSION;
# endif /* defined(MNT2_UDF_OPT_CLOSESESSION) && defined(MNTTAB_OPT_CLOSESESSION) */
#endif /* HAVE_UDF_ARGS_T_UDFMFLAGS */

#ifdef HAVE_UDF_ARGS_T_NOBODY_UID
	udf_args.nobody_uid = uid_nobody;
#endif /* HAVE_UDF_ARGS_T_NOBODY_UID */

#ifdef HAVE_UDF_ARGS_T_NOBODY_GID
	udf_args.nobody_gid = gid_nobody;
#endif /* HAVE_UDF_ARGS_T_NOBODY_GID */

#ifdef HAVE_UDF_ARGS_T_ANON_UID
	udf_args.anon_uid = uid_nobody;	/* default to nobody */
	if ((str = hasmntstr(&mnt, MNTTAB_OPT_USER)) != NULL) {
		udf_args.anon_uid = a_uid(str, MNTTAB_OPT_USER);
		XFREE(str);
	}
#endif /* HAVE_UDF_ARGS_T_ANON_UID */

#ifdef HAVE_UDF_ARGS_T_ANON_GID
	udf_args.anon_gid = gid_nobody;	/* default to nobody */
	if ((str = hasmntstr(&mnt, MNTTAB_OPT_GROUP)) != NULL) {
		udf_args.anon_gid = a_gid(str, MNTTAB_OPT_GROUP);
		XFREE(str);
	}
#endif /* HAVE_UDF_ARGS_T_ANON_GID */

#ifdef HAVE_UDF_ARGS_T_GMTOFF
	udf_args.gmtoff = 0;
	if ((str = hasmntstr(&mnt, MNTTAB_OPT_GMTOFF)) != NULL) {
		udf_args.gmtoff = a_num(str, MNTTAB_OPT_GMTOFF);
		XFREE(str);
	}
#endif /* HAVE_UDF_ARGS_T_GMTOFF */

#ifdef HAVE_UDF_ARGS_T_SESSIONNR
	udf_args.sessionnr = 0;
	if ((str = hasmntstr(&mnt, MNTTAB_OPT_SESSIONNR)) != NULL) {
		udf_args.sessionnr = a_num(str, MNTTAB_OPT_SESSIONNR);
		XFREE(str);
	}
#endif /* HAVE_UDF_ARGS_T_SESSIONNR */

#ifdef HAVE_UDF_ARGS_T_VERSION
# ifdef UDFMNT_VERSION
	udf_args.version = UDFMNT_VERSION;
# endif /* UDFMNT_VERSION */
#endif /* HAVE_UDF_ARGS_T_VERSION */

#ifdef HAVE_UDF_ARGS_T_FSPEC
	udf_args.fspec = fs_name;
#endif /* HAVE_UFS_ARGS_T_FSPEC */

	/*
	 * Call generic mount routine
	 */
	return mount_fs(&mnt, flags, (caddr_t)&udf_args, 0, type, 0, NULL,
	    mnttab_file_name, on_autofs);
}