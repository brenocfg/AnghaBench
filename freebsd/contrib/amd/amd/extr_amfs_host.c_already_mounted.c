#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* mnt; struct TYPE_5__* mnext; } ;
typedef  TYPE_2__ mntlist ;
struct TYPE_4__ {int /*<<< orphan*/  mnt_dir; } ;

/* Variables and functions */
 scalar_t__ STREQ (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
already_mounted(mntlist *mlist, char *dir)
{
  mntlist *ml;

  for (ml = mlist; ml; ml = ml->mnext)
    if (STREQ(ml->mnt->mnt_dir, dir))
      return 1;
  return 0;
}