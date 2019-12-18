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
struct zone {int dummy; } ;
struct thread_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_KERNEL_STACK ; 
 int /*<<< orphan*/  mod_zone_page_state (struct zone*,int /*<<< orphan*/ ,int) ; 
 struct zone* page_zone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_page (struct thread_info*) ; 

__attribute__((used)) static void account_kernel_stack(struct thread_info *ti, int account)
{
	struct zone *zone = page_zone(virt_to_page(ti));

	mod_zone_page_state(zone, NR_KERNEL_STACK, account);
}