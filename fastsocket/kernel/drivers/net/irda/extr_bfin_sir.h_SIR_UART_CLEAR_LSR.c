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
struct bfin_sir_port {scalar_t__ membase; scalar_t__ lsr; } ;

/* Variables and functions */
 scalar_t__ OFFSET_LSR ; 
 int /*<<< orphan*/  bfin_read16 (scalar_t__) ; 

__attribute__((used)) static inline void SIR_UART_CLEAR_LSR(struct bfin_sir_port *port)
{
	port->lsr = 0;
	bfin_read16(port->membase + OFFSET_LSR);
}