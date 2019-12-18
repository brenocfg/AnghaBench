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
typedef  unsigned int u32 ;
struct yenta_socket {int dummy; } ;

/* Variables and functions */
 int CB_CSTSMASK ; 
 int CB_FCARDSTS ; 
 int /*<<< orphan*/  CB_SOCKET_EVENT ; 
 int /*<<< orphan*/  CB_SOCKET_FORCE ; 
 int /*<<< orphan*/  CB_SOCKET_MASK ; 
 int /*<<< orphan*/  I365_CSCINT ; 
 int I365_CSC_STSCHG ; 
 int /*<<< orphan*/  cb_writel (struct yenta_socket*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  exca_writeb (struct yenta_socket*,int /*<<< orphan*/ ,int) ; 
 int probe_irq_mask (unsigned long) ; 
 unsigned int probe_irq_on () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static unsigned int yenta_probe_irq(struct yenta_socket *socket, u32 isa_irq_mask)
{
	int i;
	unsigned long val;
	u32 mask;

	/*
	 * Probe for usable interrupts using the force
	 * register to generate bogus card status events.
	 */
	cb_writel(socket, CB_SOCKET_EVENT, -1);
	cb_writel(socket, CB_SOCKET_MASK, CB_CSTSMASK);
	exca_writeb(socket, I365_CSCINT, 0);
	val = probe_irq_on() & isa_irq_mask;
	for (i = 1; i < 16; i++) {
		if (!((val >> i) & 1))
			continue;
		exca_writeb(socket, I365_CSCINT, I365_CSC_STSCHG | (i << 4));
		cb_writel(socket, CB_SOCKET_FORCE, CB_FCARDSTS);
		udelay(100);
		cb_writel(socket, CB_SOCKET_EVENT, -1);
	}
	cb_writel(socket, CB_SOCKET_MASK, 0);
	exca_writeb(socket, I365_CSCINT, 0);

	mask = probe_irq_mask(val) & 0xffff;

	return mask;
}