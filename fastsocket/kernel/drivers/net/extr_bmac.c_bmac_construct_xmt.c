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
struct sk_buff {unsigned long len; void* data; } ;
struct dbdma_cmd {int dummy; } ;

/* Variables and functions */
 int INTR_ALWAYS ; 
 int OUTPUT_LAST ; 
 int WAIT_IFCLR ; 
 int /*<<< orphan*/  dbdma_setcmd (struct dbdma_cmd volatile*,int,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long virt_to_bus (void*) ; 

__attribute__((used)) static void
bmac_construct_xmt(struct sk_buff *skb, volatile struct dbdma_cmd *cp)
{
	void *vaddr;
	unsigned long baddr;
	unsigned long len;

	len = skb->len;
	vaddr = skb->data;
	baddr = virt_to_bus(vaddr);

	dbdma_setcmd(cp, (OUTPUT_LAST | INTR_ALWAYS | WAIT_IFCLR), len, baddr, 0);
}