#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ submodel; } ;
typedef  TYPE_1__ sb_devc ;

/* Variables and functions */
 scalar_t__ SUBMDL_ES1887 ; 
 int ess_common_set_irq_hw (TYPE_1__*) ; 
 int /*<<< orphan*/  ess_es1887_set_irq_hw (TYPE_1__*) ; 

__attribute__((used)) static int ess_set_irq_hw (sb_devc * devc)
{
	if (devc->submodel == SUBMDL_ES1887) ess_es1887_set_irq_hw (devc);

	return ess_common_set_irq_hw (devc);
}