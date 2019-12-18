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
struct mask_info {struct mask_info* next; int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 struct mask_info book_info ; 
 struct mask_info core_info ; 
 int /*<<< orphan*/  cpus_clear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clear_masks(void)
{
	struct mask_info *info;

	info = &core_info;
	while (info) {
		cpus_clear(info->mask);
		info = info->next;
	}
#ifdef CONFIG_SCHED_BOOK
	info = &book_info;
	while (info) {
		cpus_clear(info->mask);
		info = info->next;
	}
#endif
}