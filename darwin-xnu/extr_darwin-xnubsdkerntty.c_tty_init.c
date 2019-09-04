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

/* Variables and functions */
 int /*<<< orphan*/  lck_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/  tty_lck_attr ; 
 int /*<<< orphan*/  tty_lck_grp ; 
 int /*<<< orphan*/  tty_lck_grp_attr ; 

void
tty_init(void)
{
	tty_lck_grp_attr = lck_grp_attr_alloc_init();
	tty_lck_grp = lck_grp_alloc_init("tty",  tty_lck_grp_attr);
	tty_lck_attr = lck_attr_alloc_init();
}