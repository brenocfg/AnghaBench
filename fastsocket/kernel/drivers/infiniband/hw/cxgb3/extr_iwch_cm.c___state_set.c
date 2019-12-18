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
struct iwch_ep_common {int state; } ;
typedef  enum iwch_ep_state { ____Placeholder_iwch_ep_state } iwch_ep_state ;

/* Variables and functions */

__attribute__((used)) static void __state_set(struct iwch_ep_common *epc, enum iwch_ep_state new)
{
	epc->state = new;
}