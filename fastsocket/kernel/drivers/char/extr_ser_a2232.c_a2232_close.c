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
 int /*<<< orphan*/  a2232_disable_rx_interrupts (void*) ; 
 int /*<<< orphan*/  a2232_disable_tx_interrupts (void*) ; 

__attribute__((used)) static void a2232_close(void *ptr)
{
	a2232_disable_tx_interrupts(ptr);
	a2232_disable_rx_interrupts(ptr);
	/* see the comment in a2232_shutdown_port above. */
}