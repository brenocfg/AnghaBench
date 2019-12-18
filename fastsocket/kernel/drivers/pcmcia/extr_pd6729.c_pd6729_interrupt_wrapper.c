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
struct pd6729_socket {int /*<<< orphan*/  poll_timer; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pd6729_interrupt (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void pd6729_interrupt_wrapper(unsigned long data)
{
	struct pd6729_socket *socket = (struct pd6729_socket *) data;

	pd6729_interrupt(0, (void *)socket);
	mod_timer(&socket->poll_timer, jiffies + HZ);
}