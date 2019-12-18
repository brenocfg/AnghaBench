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
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int __cpcmd (char const*,char*,int,int*) ; 
 int /*<<< orphan*/  cpcmd_lock ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long virt_to_phys (char*) ; 

int cpcmd(const char *cmd, char *response, int rlen, int *response_code)
{
	char *lowbuf;
	int len;
	unsigned long flags;

	if ((virt_to_phys(response) != (unsigned long) response) ||
			(((unsigned long)response + rlen) >> 31)) {
		lowbuf = kmalloc(rlen, GFP_KERNEL | GFP_DMA);
		if (!lowbuf) {
			pr_warning("The cpcmd kernel function failed to "
				   "allocate a response buffer\n");
			return -ENOMEM;
		}
		spin_lock_irqsave(&cpcmd_lock, flags);
		len = __cpcmd(cmd, lowbuf, rlen, response_code);
		spin_unlock_irqrestore(&cpcmd_lock, flags);
		memcpy(response, lowbuf, rlen);
		kfree(lowbuf);
	} else {
		spin_lock_irqsave(&cpcmd_lock, flags);
		len = __cpcmd(cmd, response, rlen, response_code);
		spin_unlock_irqrestore(&cpcmd_lock, flags);
	}
	return len;
}