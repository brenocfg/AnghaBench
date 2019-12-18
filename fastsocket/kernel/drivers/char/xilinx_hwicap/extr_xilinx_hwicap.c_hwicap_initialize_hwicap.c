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
typedef  int /*<<< orphan*/  u32 ;
struct hwicap_drvdata {int /*<<< orphan*/  dev; TYPE_1__* config_regs; TYPE_2__* config; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* reset ) (struct hwicap_drvdata*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  IDCODE; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int hwicap_command_desync (struct hwicap_drvdata*) ; 
 int hwicap_get_configuration_register (struct hwicap_drvdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct hwicap_drvdata*) ; 

__attribute__((used)) static int hwicap_initialize_hwicap(struct hwicap_drvdata *drvdata)
{
	int status;
	u32 idcode;

	dev_dbg(drvdata->dev, "initializing\n");

	/* Abort any current transaction, to make sure we have the
	 * ICAP in a good state. */
	dev_dbg(drvdata->dev, "Reset...\n");
	drvdata->config->reset(drvdata);

	dev_dbg(drvdata->dev, "Desync...\n");
	status = hwicap_command_desync(drvdata);
	if (status)
		return status;

	/* Attempt to read the IDCODE from ICAP.  This
	 * may not be returned correctly, due to the design of the
	 * hardware.
	 */
	dev_dbg(drvdata->dev, "Reading IDCODE...\n");
	status = hwicap_get_configuration_register(
			drvdata, drvdata->config_regs->IDCODE, &idcode);
	dev_dbg(drvdata->dev, "IDCODE = %x\n", idcode);
	if (status)
		return status;

	dev_dbg(drvdata->dev, "Desync...\n");
	status = hwicap_command_desync(drvdata);
	if (status)
		return status;

	return 0;
}