#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  am_flags; TYPE_2__* am_al; struct TYPE_9__* am_child; struct TYPE_9__* am_ysib; struct TYPE_9__* am_osib; struct TYPE_9__* am_parent; } ;
typedef  TYPE_3__ am_node ;
struct TYPE_8__ {TYPE_1__* al_mnt; } ;
struct TYPE_7__ {int mf_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMF_AUTOFS ; 
 int /*<<< orphan*/  AMF_ROOT ; 
 int MFF_IS_AUTOFS ; 
 TYPE_3__* root_node ; 

void
insert_am(am_node *mp, am_node *p_mp)
{
  /*
   * If this is going in at the root then flag it
   * so that it cannot be unmounted by amq.
   */
  if (p_mp == root_node)
    mp->am_flags |= AMF_ROOT;
  /*
   * Fill in n-way links
   */
  mp->am_parent = p_mp;
  mp->am_osib = p_mp->am_child;
  if (mp->am_osib)
    mp->am_osib->am_ysib = mp;
  p_mp->am_child = mp;
#ifdef HAVE_FS_AUTOFS
  if (p_mp->am_al->al_mnt->mf_flags & MFF_IS_AUTOFS)
    mp->am_flags |= AMF_AUTOFS;
#endif /* HAVE_FS_AUTOFS */
}