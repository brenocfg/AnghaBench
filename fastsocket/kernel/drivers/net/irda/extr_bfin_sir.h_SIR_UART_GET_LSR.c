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
struct bfin_sir_port {unsigned int lsr; scalar_t__ membase; } ;

/* Variables and functions */
 unsigned int BI ; 
 unsigned int FE ; 
 unsigned int OE ; 
 scalar_t__ OFFSET_LSR ; 
 unsigned int PE ; 
 unsigned int bfin_read16 (scalar_t__) ; 

__attribute__((used)) static inline unsigned int SIR_UART_GET_LSR(struct bfin_sir_port *port)
{
	unsigned int lsr = bfin_read16(port->membase + OFFSET_LSR);
	port->lsr |= (lsr & (BI|FE|PE|OE));
	return lsr | port->lsr;
}