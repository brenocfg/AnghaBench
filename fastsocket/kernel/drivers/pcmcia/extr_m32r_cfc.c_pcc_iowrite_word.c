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
typedef  int u_long ;

/* Variables and functions */
 int /*<<< orphan*/  debug (int,char*,int,...) ; 
 int /*<<< orphan*/  pcc_lock ; 
 int pcc_port2addr (unsigned long,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,int) ; 

void pcc_iowrite_word(int sock, unsigned long port, void *buf, size_t size,
	size_t nmemb, int flag)
{
	u_long addr;
	unsigned short *bp = (unsigned short *)buf;
	unsigned long flags;

	debug(3, "m32r_cfc: pcc_iowrite_word: sock=%d, port=%#lx, "
		 "buf=%p, size=%u, nmemb=%d, flag=%d\n",
		 sock, port, buf, size, nmemb, flag);

	if(size != 2)
		printk("m32r_cfc: iowrite_word :illigal size %u : %#lx\n",
			size, port);
	if(size == 9)
		printk("m32r_cfc: iowrite_word :outsw \n");

	addr = pcc_port2addr(port, 2);
	if (!addr) {
		printk("m32r_cfc:iowrite_word null addr :%#lx\n",port);
		return;
	}
#if 1
	if (addr & 1) {
		printk("m32r_cfc:iowrite_word port addr (%#lx):%#lx\n", port,
			addr);
		return;
	}
#endif
	debug(3, "m32r_cfc: pcc_iowrite_word: addr=%#lx\n", addr);

	spin_lock_irqsave(&pcc_lock, flags);
	while (nmemb--)
		writew(*bp++, addr);
	spin_unlock_irqrestore(&pcc_lock, flags);
}