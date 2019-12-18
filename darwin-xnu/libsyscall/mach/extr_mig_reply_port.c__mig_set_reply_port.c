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
 int /*<<< orphan*/  __TSD_MIG_REPLY ; 
 int /*<<< orphan*/  _os_tsd_set_direct (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static inline void
_mig_set_reply_port(mach_port_t port)
{
	_os_tsd_set_direct(__TSD_MIG_REPLY, (void *)(uintptr_t)port);
}