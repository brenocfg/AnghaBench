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
typedef  unsigned char u_char ;
struct cyclades_port {int line; } ;

/* Variables and functions */
 scalar_t__ BASE_ADDR ; 
 size_t CyCAR ; 
 size_t CyIER ; 
 unsigned char volatile CyTxMpty ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

void start_xmit(struct cyclades_port *info)
{
	unsigned long flags;
	volatile unsigned char *base_addr = (u_char *) BASE_ADDR;
	int channel;

	channel = info->line;
	local_irq_save(flags);
	base_addr[CyCAR] = channel;
	base_addr[CyIER] |= CyTxMpty;
	local_irq_restore(flags);
}