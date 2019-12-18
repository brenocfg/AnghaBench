#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  irq_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ps3_irq_plug_destroy (int /*<<< orphan*/ ) ; 
 TYPE_1__ the_card ; 

__attribute__((used)) static void snd_ps3_free_irq(void)
{
	free_irq(the_card.irq_no, &the_card);
	ps3_irq_plug_destroy(the_card.irq_no);
}