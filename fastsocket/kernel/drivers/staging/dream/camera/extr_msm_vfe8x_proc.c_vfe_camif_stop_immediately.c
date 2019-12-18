#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ vfebase; } ;

/* Variables and functions */
 scalar_t__ CAMIF_COMMAND ; 
 int /*<<< orphan*/  CAMIF_COMMAND_STOP_IMMEDIATELY ; 
 scalar_t__ VFE_CGC_OVERRIDE ; 
 TYPE_1__* ctrl ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void vfe_camif_stop_immediately(void)
{
	writel(CAMIF_COMMAND_STOP_IMMEDIATELY, ctrl->vfebase + CAMIF_COMMAND);
	writel(0, ctrl->vfebase + VFE_CGC_OVERRIDE);
}