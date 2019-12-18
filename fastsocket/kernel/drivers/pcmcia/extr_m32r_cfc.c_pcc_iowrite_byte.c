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
typedef  int /*<<< orphan*/  u_long ;

/* Variables and functions */
 int /*<<< orphan*/  debug (int,char*,int,...) ; 
 int /*<<< orphan*/  pcc_lock ; 
 int /*<<< orphan*/  pcc_port2addr (unsigned long,int) ; 
 int /*<<< orphan*/  printk (char*,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pcc_iowrite_byte(int sock, unsigned long port, void *buf, size_t size,
	size_t nmemb, int flag)
{
	u_long addr;
	unsigned char *bp = (unsigned char *)buf;
	unsigned long flags;

	debug(3, "m32r_cfc: pcc_iowrite_byte: sock=%d, port=%#lx, "
		 "buf=%p, size=%u, nmemb=%d, flag=%d\n",
		 sock, port, buf, size, nmemb, flag);

	/* write Byte */
	addr = pcc_port2addr(port, 1);
	if (!addr) {
		printk("m32r_cfc:iowrite_byte null port:%#lx\n",port);
		return;
	}
	debug(3, "m32r_cfc: pcc_iowrite_byte: addr=%#lx\n", addr);

	spin_lock_irqsave(&pcc_lock, flags);
	while (nmemb--)
		writeb(*bp++, addr);
	spin_unlock_irqrestore(&pcc_lock, flags);
}