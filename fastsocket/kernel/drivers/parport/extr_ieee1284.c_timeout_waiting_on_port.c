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
 unsigned long PARPORT_MAX ; 
 int /*<<< orphan*/  parport_ieee1284_wakeup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * port_from_cookie ; 

__attribute__((used)) static void timeout_waiting_on_port (unsigned long cookie)
{
	parport_ieee1284_wakeup (port_from_cookie[cookie % PARPORT_MAX]);
}