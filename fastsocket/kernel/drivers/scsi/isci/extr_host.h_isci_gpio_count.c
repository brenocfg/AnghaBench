#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct isci_host {TYPE_3__* scu_registers; } ;
struct TYPE_4__ {int /*<<< orphan*/  output_data_select; } ;
struct TYPE_5__ {TYPE_1__ sgpio; } ;
struct TYPE_6__ {TYPE_2__ peg0; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int isci_gpio_count(struct isci_host *ihost)
{
	return ARRAY_SIZE(ihost->scu_registers->peg0.sgpio.output_data_select);
}