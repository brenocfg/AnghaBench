#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ mf_error; int mf_flags; TYPE_1__* mf_server; } ;
typedef  TYPE_3__ mntfs ;
struct TYPE_10__ {scalar_t__ am_error; struct TYPE_10__* am_osib; TYPE_2__* am_al; } ;
typedef  TYPE_4__ am_node ;
struct TYPE_8__ {TYPE_3__* al_mnt; } ;
struct TYPE_7__ {int fs_flags; } ;

/* Variables and functions */
 int FSF_DOWN ; 
 int MFF_MOUNTED ; 

am_node *
next_nonerror_node(am_node *xp)
{
  mntfs *mf;

  /*
   * Bug report (7/12/89) from Rein Tollevik <rein@ifi.uio.no>
   * Fixes a race condition when mounting direct automounts.
   * Also fixes a problem when doing a readdir on a directory
   * containing hung automounts.
   */
  while (xp &&
	 (!(mf = xp->am_al->al_mnt) ||	/* No mounted filesystem */
	  mf->mf_error != 0 ||	/* There was a mntfs error */
	  xp->am_error != 0 ||	/* There was a mount error */
	  !(mf->mf_flags & MFF_MOUNTED) ||	/* The fs is not mounted */
	  (mf->mf_server->fs_flags & FSF_DOWN))	/* The fs may be down */
	 )
    xp = xp->am_osib;

  return xp;
}