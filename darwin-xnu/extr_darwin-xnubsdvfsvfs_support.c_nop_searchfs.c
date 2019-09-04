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
struct vnop_searchfs_args {scalar_t__* a_nummatches; } ;

/* Variables and functions */

int
nop_searchfs(struct vnop_searchfs_args *ap)
{
	*(ap->a_nummatches) = 0;
	return (0);
}