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
struct uart_cpm_port {int flags; } ;

/* Variables and functions */
 int FLAG_CONSOLE ; 
 int /*<<< orphan*/  cpm_uart_freebuf (struct uart_cpm_port*) ; 

__attribute__((used)) static void cpm_uart_release_port(struct uart_port *port)
{
	struct uart_cpm_port *pinfo = (struct uart_cpm_port *)port;

	if (!(pinfo->flags & FLAG_CONSOLE))
		cpm_uart_freebuf(pinfo);
}