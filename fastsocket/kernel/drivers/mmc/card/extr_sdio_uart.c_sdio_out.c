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
struct sdio_uart_port {scalar_t__ regs_offset; int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int /*<<< orphan*/  sdio_writeb (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void sdio_out(struct sdio_uart_port *port, int offset, int value)
{
	sdio_writeb(port->func, value, port->regs_offset + offset, NULL);
}