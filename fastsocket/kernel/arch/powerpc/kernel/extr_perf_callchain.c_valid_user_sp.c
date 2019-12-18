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
 int TASK_SIZE ; 

__attribute__((used)) static inline int valid_user_sp(unsigned long sp, int is_64)
{
	if (!sp || (sp & 7) || sp > TASK_SIZE - 32)
		return 0;
	return 1;
}