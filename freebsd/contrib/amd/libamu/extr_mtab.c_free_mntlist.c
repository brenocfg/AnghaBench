#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  mntlist ;

/* Variables and functions */
 int /*<<< orphan*/  discard_mntlist (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_mntlist () ; 

void
free_mntlist(mntlist *mp)
{
  discard_mntlist(mp);
#ifdef MOUNT_TABLE_ON_FILE
  unlock_mntlist();
#endif /* MOUNT_TABLE_ON_FILE */
}