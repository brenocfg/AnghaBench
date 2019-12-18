#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hpfs_creation_de; } ;

/* Variables and functions */
 TYPE_1__* hpfs_sb (struct super_block*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

void hpfs_unlock_creation(struct super_block *s)
{
#ifdef DEBUG_LOCKS
	printk("unlock creation\n");
#endif
	up(&hpfs_sb(s)->hpfs_creation_de);
}