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
struct restart_block {int dummy; } ;

/* Variables and functions */
 long EINVAL ; 

__attribute__((used)) static long process_cpu_nsleep_restart(struct restart_block *restart_block)
{
	return -EINVAL;
}