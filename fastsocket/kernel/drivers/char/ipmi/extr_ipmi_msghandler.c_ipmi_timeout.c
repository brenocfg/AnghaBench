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
 scalar_t__ IPMI_REQUEST_EV_TIME ; 
 scalar_t__ IPMI_TIMEOUT_JIFFIES ; 
 int /*<<< orphan*/  IPMI_TIMEOUT_TIME ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipmi_request_event () ; 
 int /*<<< orphan*/  ipmi_timeout_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipmi_timer ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  stop_operation ; 
 scalar_t__ ticks_to_req_ev ; 

__attribute__((used)) static void ipmi_timeout(unsigned long data)
{
	if (atomic_read(&stop_operation))
		return;

	ticks_to_req_ev--;
	if (ticks_to_req_ev == 0) {
		ipmi_request_event();
		ticks_to_req_ev = IPMI_REQUEST_EV_TIME;
	}

	ipmi_timeout_handler(IPMI_TIMEOUT_TIME);

	mod_timer(&ipmi_timer, jiffies + IPMI_TIMEOUT_JIFFIES);
}