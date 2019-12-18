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
struct tipc_port {int /*<<< orphan*/  ref; } ;
typedef  int /*<<< orphan*/  Handler ;

/* Variables and functions */
 scalar_t__ port_wakeup_sh ; 
 int /*<<< orphan*/  tipc_k_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void port_wakeup(struct tipc_port *p_ptr)
{
	tipc_k_signal((Handler)port_wakeup_sh, p_ptr->ref);
}