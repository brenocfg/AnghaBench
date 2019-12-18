#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ mnt; struct TYPE_4__* mnext; } ;
typedef  TYPE_1__ mntlist ;

/* Variables and functions */
 int /*<<< orphan*/  XFREE (TYPE_1__*) ; 
 int /*<<< orphan*/  mnt_free (scalar_t__) ; 

void
discard_mntlist(mntlist *mp)
{
  mntlist *mp2;

  while ((mp2 = mp)) {
    mp = mp->mnext;
    if (mp2->mnt)
      mnt_free(mp2->mnt);
    XFREE(mp2);
  }
}