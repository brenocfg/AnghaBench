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
typedef  int uint32_t ;
struct ioc4_port {int ip_ienb; int /*<<< orphan*/  ip_ioc4_soft; struct hooks* ip_hooks; } ;
struct hooks {int intr_dma_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOC4_OTHER_INTR_TYPE ; 
 int /*<<< orphan*/  IOC4_SIO_INTR_TYPE ; 
 int /*<<< orphan*/  IOC4_W_IEC ; 
 int /*<<< orphan*/  write_ireg (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void disable_intrs(struct ioc4_port *port, uint32_t mask)
{
	struct hooks *hooks = port->ip_hooks;

	if (port->ip_ienb & mask) {
		write_ireg(port->ip_ioc4_soft, mask, IOC4_W_IEC,
					IOC4_SIO_INTR_TYPE);
		port->ip_ienb &= ~mask;
	}

	if (!port->ip_ienb)
		write_ireg(port->ip_ioc4_soft, hooks->intr_dma_error,
				IOC4_W_IEC, IOC4_OTHER_INTR_TYPE);
}