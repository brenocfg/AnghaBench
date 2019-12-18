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
 int /*<<< orphan*/  LLC_CONN_EV_TYPE_ACK_TMR ; 
 int /*<<< orphan*/  llc_conn_tmr_common_cb (unsigned long,int /*<<< orphan*/ ) ; 

void llc_conn_ack_tmr_cb(unsigned long timeout_data)
{
	llc_conn_tmr_common_cb(timeout_data, LLC_CONN_EV_TYPE_ACK_TMR);
}