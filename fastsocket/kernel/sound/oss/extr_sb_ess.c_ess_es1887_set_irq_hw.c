#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;
typedef  TYPE_1__ sb_devc ;

/* Variables and functions */
 int /*<<< orphan*/  ess_chgmixer (TYPE_1__*,int,int,int) ; 
 int ess_irq_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ess_es1887_set_irq_hw (sb_devc * devc)
{
	int irq_bits;

	if ((irq_bits = ess_irq_bits (devc->irq)) == -1) return;

	ess_chgmixer (devc, 0x7f, 0x0f, 0x01 | ((irq_bits + 1) << 1));
}