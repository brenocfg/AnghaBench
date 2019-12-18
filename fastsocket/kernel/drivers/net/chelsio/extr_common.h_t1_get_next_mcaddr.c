#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct t1_rx_mode {TYPE_2__* list; TYPE_1__* dev; int /*<<< orphan*/  idx; } ;
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/ * dmi_addr; } ;
struct TYPE_3__ {scalar_t__ mc_count; } ;

/* Variables and functions */

__attribute__((used)) static inline u8 *t1_get_next_mcaddr(struct t1_rx_mode *rm)
{
	u8 *addr = NULL;

	if (rm->idx++ < rm->dev->mc_count) {
		addr = rm->list->dmi_addr;
		rm->list = rm->list->next;
	}
	return addr;
}