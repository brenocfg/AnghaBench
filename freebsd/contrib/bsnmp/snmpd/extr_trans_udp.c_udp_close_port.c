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
struct udp_port {int /*<<< orphan*/  input; } ;
struct tport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct udp_port*) ; 
 int /*<<< orphan*/  snmpd_input_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trans_remove_port (struct tport*) ; 

__attribute__((used)) static void
udp_close_port(struct tport *tp)
{
	struct udp_port *port = (struct udp_port *)tp;

	snmpd_input_close(&port->input);
	trans_remove_port(tp);
	free(port);
}