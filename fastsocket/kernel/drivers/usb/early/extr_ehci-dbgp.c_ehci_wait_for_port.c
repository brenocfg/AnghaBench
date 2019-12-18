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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int ENOTCONN ; 
 int STS_PCD ; 
 int /*<<< orphan*/  dbgp_mdelay (int) ; 
 TYPE_1__* ehci_regs ; 
 int ehci_reset_port (int) ; 
 int readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ehci_wait_for_port(int port)
{
	u32 status;
	int ret, reps;

	for (reps = 0; reps < 300; reps++) {
		status = readl(&ehci_regs->status);
		if (status & STS_PCD)
			break;
		dbgp_mdelay(1);
	}
	ret = ehci_reset_port(port);
	if (ret == 0)
		return 0;
	return -ENOTCONN;
}