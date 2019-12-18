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
struct tport {int dummy; } ;
struct inet_port {struct inet_port* dns_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  deactivate_port (struct inet_port*) ; 
 int /*<<< orphan*/  free (struct inet_port*) ; 
 int /*<<< orphan*/  trans_remove_port (struct tport*) ; 

__attribute__((used)) static void
inet_destroy_port(struct tport *tp)
{
	struct inet_port *port = (struct inet_port *)tp;

	deactivate_port(port);

	trans_remove_port(tp);

	free(port->dns_addr);
	free(port);
}