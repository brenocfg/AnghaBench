#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {char* am_link; TYPE_3__* am_al; } ;
typedef  TYPE_4__ am_node ;
struct TYPE_10__ {TYPE_2__* al_mnt; } ;
struct TYPE_9__ {char* mf_mount; TYPE_1__* mf_ops; } ;
struct TYPE_8__ {TYPE_4__* (* readlink ) (TYPE_4__*,int*) ;} ;

/* Variables and functions */
 TYPE_4__* stub1 (TYPE_4__*,int*) ; 

__attribute__((used)) static char *
do_readlink(am_node *mp, int *error_return)
{
  char *ln;

  /*
   * If there is a readlink method then use it,
   * otherwise if a link exists use that,
   * otherwise use the mount point.
   */
  if (mp->am_al->al_mnt->mf_ops->readlink) {
    int retry = 0;
    mp = (*mp->am_al->al_mnt->mf_ops->readlink) (mp, &retry);
    if (mp == NULL) {
      *error_return = retry;
      return 0;
    }
    /* reschedule_timeout_mp(); */
  }

  if (mp->am_link) {
    ln = mp->am_link;
  } else {
    ln = mp->am_al->al_mnt->mf_mount;
  }

  return ln;
}