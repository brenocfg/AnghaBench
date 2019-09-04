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
typedef  int /*<<< orphan*/  proc_t ;

/* Variables and functions */
 int /*<<< orphan*/  vfork_exit_internal (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
vfork_exit(proc_t p, int rv)
{
	vfork_exit_internal(p, rv, 0);
}