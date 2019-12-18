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
typedef  int /*<<< orphan*/  mach_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  MACH_PORT_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _tsd_get_special_reply_port () ; 
 int /*<<< orphan*/  _tsd_set_special_reply_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_get_special_reply_port () ; 

mach_port_t
mig_get_special_reply_port(void)
{
	mach_port_t srp;

	srp = _tsd_get_special_reply_port();
	if (!MACH_PORT_VALID(srp)) {
		srp = thread_get_special_reply_port();
		_tsd_set_special_reply_port(srp);
	}

	return srp;
}