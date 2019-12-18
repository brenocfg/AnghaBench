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
struct turnstile {int dummy; } ;
typedef  scalar_t__ ipc_port_t ;

/* Variables and functions */
 struct turnstile* turnstile_lookup_by_proprietor (uintptr_t) ; 

struct turnstile *
ipc_port_rcv_turnstile(ipc_port_t port)
{
	return turnstile_lookup_by_proprietor((uintptr_t)port);
}