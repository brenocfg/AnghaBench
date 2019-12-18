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
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_EV_RXCHAR ; 
 int /*<<< orphan*/  PORT_SetEventCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PORT_SetEventMask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_hf_client_port_cback ; 

void bta_hf_client_setup_port(UINT16 handle)
{
    PORT_SetEventMask(handle, PORT_EV_RXCHAR);
    PORT_SetEventCallback(handle, bta_hf_client_port_cback);
}