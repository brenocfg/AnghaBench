#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  CAP_ENDPTCOMPLETE ; 
 int /*<<< orphan*/  CAP_ENDPTFLUSH ; 
 int /*<<< orphan*/  CAP_ENDPTPRIME ; 
 int /*<<< orphan*/  CAP_ENDPTSETUPSTAT ; 
 scalar_t__ hw_cread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_cwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_usb_set_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int hw_usb_reset(void)
{
	hw_usb_set_address(0);

	/* ESS flushes only at end?!? */
	hw_cwrite(CAP_ENDPTFLUSH,    ~0, ~0);   /* flush all EPs */

	/* clear setup token semaphores */
	hw_cwrite(CAP_ENDPTSETUPSTAT, 0,  0);   /* writes its content */

	/* clear complete status */
	hw_cwrite(CAP_ENDPTCOMPLETE,  0,  0);   /* writes its content */

	/* wait until all bits cleared */
	while (hw_cread(CAP_ENDPTPRIME, ~0))
		udelay(10);             /* not RTOS friendly */

	/* reset all endpoints ? */

	/* reset internal status and wait for further instructions
	   no need to verify the port reset status (ESS does it) */

	return 0;
}