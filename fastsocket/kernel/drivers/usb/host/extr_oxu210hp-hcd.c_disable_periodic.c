#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct oxu_hcd {int next_uframe; TYPE_1__* regs; } ;
struct TYPE_5__ {int /*<<< orphan*/  state; } ;
struct TYPE_4__ {int /*<<< orphan*/  command; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int CMD_PSE ; 
 int /*<<< orphan*/  HC_STATE_HALT ; 
 int /*<<< orphan*/  STS_PSS ; 
 int handshake (struct oxu_hcd*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* oxu_to_hcd (struct oxu_hcd*) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_hc_died (TYPE_2__*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int disable_periodic(struct oxu_hcd *oxu)
{
	u32 cmd;
	int status;

	/* did setting PSE not take effect yet?
	 * takes effect only at frame boundaries...
	 */
	status = handshake(oxu, &oxu->regs->status, STS_PSS, STS_PSS, 9 * 125);
	if (status != 0) {
		oxu_to_hcd(oxu)->state = HC_STATE_HALT;
		usb_hc_died(oxu_to_hcd(oxu));
		return status;
	}

	cmd = readl(&oxu->regs->command) & ~CMD_PSE;
	writel(cmd, &oxu->regs->command);
	/* posted write ... */

	oxu->next_uframe = -1;
	return 0;
}