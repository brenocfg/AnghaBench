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

/* Variables and functions */
 unsigned int RBTX4939_IRQ_IOC ; 
 int /*<<< orphan*/  rbtx4939_ien_addr ; 
 int readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rbtx4939_ioc_irq_unmask(unsigned int irq)
{
	int ioc_nr = irq - RBTX4939_IRQ_IOC;

	writeb(readb(rbtx4939_ien_addr) | (1 << ioc_nr), rbtx4939_ien_addr);
}