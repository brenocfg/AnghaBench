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
struct dpages {unsigned long context_u; void* context_ptr; int /*<<< orphan*/  next_page; int /*<<< orphan*/  get_page; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  km_get_page ; 
 int /*<<< orphan*/  km_next_page ; 

__attribute__((used)) static void km_dp_init(struct dpages *dp, void *data)
{
	dp->get_page = km_get_page;
	dp->next_page = km_next_page;
	dp->context_u = ((unsigned long) data) & (PAGE_SIZE - 1);
	dp->context_ptr = data;
}