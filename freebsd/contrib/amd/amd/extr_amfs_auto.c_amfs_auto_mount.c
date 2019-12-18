#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  opts ;
struct TYPE_18__ {char* mf_info; int mf_flags; TYPE_4__* mf_fo; } ;
typedef  TYPE_6__ mntfs ;
struct TYPE_19__ {int /*<<< orphan*/  am_autofs_fh; int /*<<< orphan*/  am_name; void* am_pref; TYPE_5__* am_parent; } ;
typedef  TYPE_7__ am_node ;
struct TYPE_13__ {int /*<<< orphan*/  na_nlink; } ;
struct TYPE_17__ {char* am_pref; TYPE_3__* am_al; TYPE_1__ am_fattr; } ;
struct TYPE_16__ {char* opt_pref; } ;
struct TYPE_15__ {TYPE_2__* al_mnt; } ;
struct TYPE_14__ {int /*<<< orphan*/  mf_info; } ;

/* Variables and functions */
 int EINVAL ; 
 int MFF_IS_AUTOFS ; 
 int SIZEOF_OPTS ; 
 scalar_t__ STREQ (char*,char*) ; 
 int /*<<< orphan*/  XLOG_FATAL ; 
 int /*<<< orphan*/  amfs_mkcacheref (TYPE_6__*) ; 
 int amfs_mount (TYPE_7__*,TYPE_6__*,char*) ; 
 int /*<<< orphan*/  autofs_get_opts (char*,int,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*) ; 
 void* str3cat (char*,char*,int /*<<< orphan*/ ,char*) ; 
 char* strealloc (char*,int /*<<< orphan*/ ) ; 
 void* xstrdup (char*) ; 

__attribute__((used)) static int
amfs_auto_mount(am_node *mp, mntfs *mf)
{
  if (mp->am_parent == NULL)
    return EINVAL;
  /*
   * Pseudo-directories are used to provide some structure
   * to the automounted directories instead
   * of putting them all in the top-level automount directory.
   *
   * Here, just increment the parent's link count.
   */
  mp->am_parent->am_fattr.na_nlink++;

  /*
   * Info field of . means use parent's info field.
   * Historical - not documented.
   */
  if (mf->mf_info[0] == '.' && mf->mf_info[1] == '\0')
    mf->mf_info = strealloc(mf->mf_info, mp->am_parent->am_al->al_mnt->mf_info);

  /*
   * Compute prefix:
   *
   * If there is an option prefix then use that else
   * If the parent had a prefix then use that with name
   *      of this node appended else
   * Use the name of this node.
   *
   * That means if you want no prefix you must say so
   * in the map.
   */
  if (mf->mf_fo->opt_pref) {
    /* allow pref:=null to set a real null prefix */
    if (STREQ(mf->mf_fo->opt_pref, "null")) {
      mp->am_pref = xstrdup("");
    } else {
      /*
       * the prefix specified as an option
       */
      mp->am_pref = xstrdup(mf->mf_fo->opt_pref);
    }
  } else {
    /*
     * else the parent's prefix
     * followed by the name
     * followed by /
     */
    char *ppref = mp->am_parent->am_pref;
    if (ppref == 0)
      ppref = "";
    mp->am_pref = str3cat((char *) NULL, ppref, mp->am_name, "/");
  }

#ifdef HAVE_FS_AUTOFS
  if (mf->mf_flags & MFF_IS_AUTOFS) {
    char opts[SIZEOF_OPTS];
    int error;

    autofs_get_opts(opts, sizeof(opts), mp->am_autofs_fh);

    /* now do the mount */
    error = amfs_mount(mp, mf, opts);
    if (error) {
      errno = error;
      plog(XLOG_FATAL, "amfs_auto_mount: amfs_mount failed: %m");
      return error;
    }
  }
#endif /* HAVE_FS_AUTOFS */

  /*
   * Attach a map cache
   */
  amfs_mkcacheref(mf);

  return 0;
}