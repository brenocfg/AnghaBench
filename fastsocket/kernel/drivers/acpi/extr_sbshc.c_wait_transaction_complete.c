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
struct acpi_smb_hc {int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int ETIME ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 scalar_t__ smb_check_done (struct acpi_smb_hc*) ; 
 scalar_t__ wait_event_timeout (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wait_transaction_complete(struct acpi_smb_hc *hc, int timeout)
{
	if (wait_event_timeout(hc->wait, smb_check_done(hc),
			       msecs_to_jiffies(timeout)))
		return 0;
	/*
	 * After the timeout happens, OS will try to check the status of SMbus.
	 * If the status is what OS expected, it will be regarded as the bogus
	 * timeout.
	 */
	if (smb_check_done(hc))
		return 0;
	else
		return -ETIME;
}