#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  state; int /*<<< orphan*/  raid_disk; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; int /*<<< orphan*/  number; } ;
typedef  TYPE_1__ mdp_disk_t ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_desc(mdp_disk_t *desc)
{
	printk(" DISK<N:%d,(%d,%d),R:%d,S:%d>\n", desc->number,
		desc->major,desc->minor,desc->raid_disk,desc->state);
}