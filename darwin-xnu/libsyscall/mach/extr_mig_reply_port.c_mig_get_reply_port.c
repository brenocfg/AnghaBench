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
typedef  scalar_t__ mach_port_t ;

/* Variables and functions */
 scalar_t__ MACH_PORT_NULL ; 
 scalar_t__ _mig_get_reply_port () ; 
 int /*<<< orphan*/  _mig_set_reply_port (scalar_t__) ; 
 scalar_t__ mach_reply_port () ; 

mach_port_t
mig_get_reply_port(void)
{
	mach_port_t port = _mig_get_reply_port();
	if (port == MACH_PORT_NULL) {
		port = mach_reply_port();
		_mig_set_reply_port(port);
	}
	return port;
}