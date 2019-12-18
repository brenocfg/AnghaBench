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

/* Variables and functions */
 int /*<<< orphan*/  SCFDR ; 
 int SCIF_TXROOM_MAX ; 
 int sci_in (struct uart_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int scif_txroom(struct uart_port *port)
{
	return SCIF_TXROOM_MAX - (sci_in(port, SCFDR) >> 8);
}