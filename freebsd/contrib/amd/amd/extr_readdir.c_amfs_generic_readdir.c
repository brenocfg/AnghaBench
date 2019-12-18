#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ voidp ;
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_13__ {scalar_t__ mnt_opts; } ;
typedef  TYPE_3__ mntent_t ;
struct TYPE_14__ {TYPE_2__* am_al; } ;
typedef  TYPE_4__ am_node ;
typedef  int /*<<< orphan*/  am_cookie3 ;
struct TYPE_12__ {TYPE_1__* al_mnt; } ;
struct TYPE_11__ {scalar_t__ mf_mopts; } ;

/* Variables and functions */
 int amfs_readdir (TYPE_4__*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int amfs_readdir3 (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int amfs_readdir3_browsable (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int amfs_readdir_browsable (TYPE_4__*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ amu_hasmntopt (TYPE_3__*,char*) ; 
 scalar_t__ nfs_dispatcher ; 
 scalar_t__ nfs_program_2 ; 

int
amfs_generic_readdir(am_node *mp, voidp cookie, voidp dp, voidp ep, u_int count)
{
  int browsable, full;

  /* check if map is browsable */
  browsable = 0;
  if (mp->am_al->al_mnt && mp->am_al->al_mnt->mf_mopts) {
    mntent_t mnt;
    mnt.mnt_opts = mp->am_al->al_mnt->mf_mopts;
    if (amu_hasmntopt(&mnt, "fullybrowsable"))
      browsable = 2;
    else if (amu_hasmntopt(&mnt, "browsable"))
      browsable = 1;
  }
  full = (browsable == 2);

  if (nfs_dispatcher == nfs_program_2) {
    if (browsable)
      return amfs_readdir_browsable(mp, cookie, dp, ep, count, full);
    else
      return amfs_readdir(mp, cookie, dp, ep, count);
  } else {
    if (browsable)
      return amfs_readdir3_browsable(mp, (am_cookie3) (uintptr_t) cookie, dp, ep, count, full);
    else
      return amfs_readdir3(mp, (am_cookie3) (uintptr_t) cookie, dp, ep, count);
  }
}