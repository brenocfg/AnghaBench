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
 int SCI_TDRE ; 
 int /*<<< orphan*/  SCxSR ; 
 int sci_in (struct uart_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int sci_txroom(struct uart_port *port)
{
	return (sci_in(port, SCxSR) & SCI_TDRE) != 0;
}