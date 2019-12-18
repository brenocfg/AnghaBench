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
typedef  scalar_t__ u8 ;
struct uart_pmac_port {int /*<<< orphan*/  control_reg; } ;

/* Variables and functions */
 scalar_t__ readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeb (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 read_zsreg(struct uart_pmac_port *port, u8 reg)
{
	if (reg != 0)
		writeb(reg, port->control_reg);
	return readb(port->control_reg);
}