#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_7__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  edit_cmdline; TYPE_1__* data; int /*<<< orphan*/  close; int /*<<< orphan*/  write; int /*<<< orphan*/  open; } ;
struct TYPE_8__ {scalar_t__ getc; } ;

/* Variables and functions */
 TYPE_7__ console_ops ; 
 int cpm_console_init (void*,TYPE_1__*) ; 
 scalar_t__ dt_is_compatible (void*,char*) ; 
 int mpc5200_psc_console_init (void*,TYPE_1__*) ; 
 int mpsc_console_init (void*,TYPE_1__*) ; 
 int ns16550_console_init (void*,TYPE_1__*) ; 
 TYPE_1__ serial_cd ; 
 int /*<<< orphan*/  serial_close ; 
 int /*<<< orphan*/  serial_edit_cmdline ; 
 void* serial_get_stdout_devp () ; 
 int /*<<< orphan*/  serial_open ; 
 int /*<<< orphan*/  serial_write ; 
 int uartlite_console_init (void*,TYPE_1__*) ; 

int serial_console_init(void)
{
	void *devp;
	int rc = -1;

	devp = serial_get_stdout_devp();
	if (devp == NULL)
		goto err_out;

	if (dt_is_compatible(devp, "ns16550") ||
	    dt_is_compatible(devp, "pnpPNP,501"))
		rc = ns16550_console_init(devp, &serial_cd);
	else if (dt_is_compatible(devp, "marvell,mv64360-mpsc"))
		rc = mpsc_console_init(devp, &serial_cd);
	else if (dt_is_compatible(devp, "fsl,cpm1-scc-uart") ||
	         dt_is_compatible(devp, "fsl,cpm1-smc-uart") ||
	         dt_is_compatible(devp, "fsl,cpm2-scc-uart") ||
	         dt_is_compatible(devp, "fsl,cpm2-smc-uart"))
		rc = cpm_console_init(devp, &serial_cd);
	else if (dt_is_compatible(devp, "fsl,mpc5200-psc-uart"))
		rc = mpc5200_psc_console_init(devp, &serial_cd);
	else if (dt_is_compatible(devp, "xlnx,opb-uartlite-1.00.b") ||
		 dt_is_compatible(devp, "xlnx,xps-uartlite-1.00.a"))
		rc = uartlite_console_init(devp, &serial_cd);

	/* Add other serial console driver calls here */

	if (!rc) {
		console_ops.open = serial_open;
		console_ops.write = serial_write;
		console_ops.close = serial_close;
		console_ops.data = &serial_cd;

		if (serial_cd.getc)
			console_ops.edit_cmdline = serial_edit_cmdline;

		return 0;
	}
err_out:
	return -1;
}