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
typedef  enum sci_port_states { ____Placeholder_sci_port_states } sci_port_states ;

/* Variables and functions */
#define  SCI_PORT_READY 131 
#define  SCI_PORT_SUB_CONFIGURING 130 
#define  SCI_PORT_SUB_OPERATIONAL 129 
#define  SCI_PORT_SUB_WAITING 128 

__attribute__((used)) static bool is_port_ready_state(enum sci_port_states state)
{
	switch (state) {
	case SCI_PORT_READY:
	case SCI_PORT_SUB_WAITING:
	case SCI_PORT_SUB_OPERATIONAL:
	case SCI_PORT_SUB_CONFIGURING:
		return true;
	default:
		return false;
	}
}