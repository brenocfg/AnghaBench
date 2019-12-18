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
 int /*<<< orphan*/  __TSD_MIG_REPLY ; 
 scalar_t__ _os_tsd_get_direct (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline mach_port_t
_mig_get_reply_port()
{
	return (mach_port_t)(uintptr_t)_os_tsd_get_direct(__TSD_MIG_REPLY);
}