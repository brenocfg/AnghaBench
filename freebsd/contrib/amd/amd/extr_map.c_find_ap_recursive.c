#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* am_child; struct TYPE_8__* am_osib; TYPE_2__* am_al; int /*<<< orphan*/  am_path; } ;
typedef  TYPE_3__ am_node ;
struct TYPE_7__ {TYPE_1__* al_mnt; } ;
struct TYPE_6__ {int mf_flags; int /*<<< orphan*/  mf_mount; } ;

/* Variables and functions */
 int MFF_MOUNTED ; 
 scalar_t__ STREQ (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static am_node *
find_ap_recursive(char *dir, am_node *mp)
{
  if (mp) {
    am_node *mp2;
    if (STREQ(mp->am_path, dir))
      return mp;

    if ((mp->am_al->al_mnt->mf_flags & MFF_MOUNTED) &&
	STREQ(mp->am_al->al_mnt->mf_mount, dir))
      return mp;

    mp2 = find_ap_recursive(dir, mp->am_osib);
    if (mp2)
      return mp2;
    return find_ap_recursive(dir, mp->am_child);
  }

  return 0;
}