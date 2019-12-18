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
typedef  int /*<<< orphan*/  u16 ;
struct ipr_ioa_cfg {scalar_t__ sdt_state; TYPE_1__* pdev; int /*<<< orphan*/  errors_logged; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ GET_DUMP ; 
 int /*<<< orphan*/  IPR_SHUTDOWN_NONE ; 
 scalar_t__ WAIT_FOR_DUMP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipr_initiate_ioa_reset (struct ipr_ioa_cfg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipr_isr_eh(struct ipr_ioa_cfg *ioa_cfg, char *msg, u16 number)
{
	ioa_cfg->errors_logged++;
	dev_err(&ioa_cfg->pdev->dev, "%s %d\n", msg, number);

	if (WAIT_FOR_DUMP == ioa_cfg->sdt_state)
		ioa_cfg->sdt_state = GET_DUMP;

	ipr_initiate_ioa_reset(ioa_cfg, IPR_SHUTDOWN_NONE);
}