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
struct bnad {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnad_disable_mbox_irq (struct bnad*) ; 

void
bnad_cb_mbox_intr_disable(struct bnad *bnad)
{
	bnad_disable_mbox_irq(bnad);
}