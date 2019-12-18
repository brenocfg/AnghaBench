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
struct oxu_hcd {int /*<<< orphan*/  actions; } ;
typedef  enum ehci_timer_action { ____Placeholder_ehci_timer_action } ehci_timer_action ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void timer_action_done(struct oxu_hcd *oxu,
					enum ehci_timer_action action)
{
	clear_bit(action, &oxu->actions);
}