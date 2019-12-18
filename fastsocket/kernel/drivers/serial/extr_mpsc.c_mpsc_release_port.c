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
struct uart_port {int dummy; } ;
struct mpsc_port_info {scalar_t__ ready; } ;

/* Variables and functions */
 int /*<<< orphan*/  mpsc_free_ring_mem (struct mpsc_port_info*) ; 
 int /*<<< orphan*/  mpsc_uninit_rings (struct mpsc_port_info*) ; 

__attribute__((used)) static void mpsc_release_port(struct uart_port *port)
{
	struct mpsc_port_info *pi = (struct mpsc_port_info *)port;

	if (pi->ready) {
		mpsc_uninit_rings(pi);
		mpsc_free_ring_mem(pi);
		pi->ready = 0;
	}
}