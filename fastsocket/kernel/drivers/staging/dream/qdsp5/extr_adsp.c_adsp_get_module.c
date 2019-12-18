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
typedef  size_t uint32_t ;
struct adsp_info {size_t** task_to_module; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long current_image ; 

uint32_t adsp_get_module(struct adsp_info *info, uint32_t task)
{
	BUG_ON(current_image == -1UL);
	return info->task_to_module[current_image][task];
}