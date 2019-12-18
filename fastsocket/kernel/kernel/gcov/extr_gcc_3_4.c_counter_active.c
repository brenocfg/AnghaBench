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
struct gcov_info {int ctr_mask; } ;

/* Variables and functions */

__attribute__((used)) static int counter_active(struct gcov_info *info, unsigned int type)
{
	return (1 << type) & info->ctr_mask;
}