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
 int /*<<< orphan*/  mbox_lock ; 
 int* mboxinuse ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int getmbox(void)
{
	unsigned long flags;
	int i;

	spin_lock_irqsave(&mbox_lock, flags);
	for(i=1;i<16;i++) if(!mboxinuse[i]) {
		mboxinuse[i]=1;
		spin_unlock_irqrestore(&mbox_lock, flags);
		return i;
	}
	spin_unlock_irqrestore(&mbox_lock, flags);
	return 0;
}