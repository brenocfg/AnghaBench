#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int mf_fsflags; } ;
typedef  TYPE_2__ mntfs ;
struct TYPE_12__ {char* am_path; TYPE_1__* am_al; } ;
typedef  TYPE_3__ am_node ;
struct TYPE_10__ {TYPE_2__* al_mnt; } ;

/* Variables and functions */
 int FS_DIRECT ; 
 int /*<<< orphan*/  dlog (char*,char*) ; 
 TYPE_3__* exported_ap_alloc () ; 
 int /*<<< orphan*/  init_map (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  insert_am (TYPE_3__*,TYPE_3__*) ; 
 char* str3cat (char*,char*,char*,char*) ; 

am_node *
get_ap_child(am_node *mp, char *fname)
{
  am_node *new_mp;
  mntfs *mf = mp->am_al->al_mnt;

  /*
   * Allocate a new map
   */
  new_mp = exported_ap_alloc();
  if (new_mp) {
    /*
     * Fill it in
     */
    init_map(new_mp, fname);

    /*
     * Put it in the table
     */
    insert_am(new_mp, mp);

    /*
     * Fill in some other fields,
     * path and mount point.
     *
     * bugfix: do not prepend old am_path if direct map
     *         <wls@astro.umd.edu> William Sebok
     */
    new_mp->am_path = str3cat(new_mp->am_path,
			      (mf->mf_fsflags & FS_DIRECT)
				     ? ""
				     : mp->am_path,
			      *fname == '/' ? "" : "/", fname);
    dlog("setting path to %s", new_mp->am_path);
  }

  return new_mp;
}