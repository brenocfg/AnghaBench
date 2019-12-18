#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int flags; } ;
struct smsc911x_data {int ioaddr; int /*<<< orphan*/  dev_lock; TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int SMSC911X_USE_16BIT ; 
 int SMSC911X_USE_32BIT ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,int) ; 
 int /*<<< orphan*/  writew (int,int) ; 

__attribute__((used)) static inline void smsc911x_reg_write(struct smsc911x_data *pdata, u32 reg,
				      u32 val)
{
	if (pdata->config.flags & SMSC911X_USE_32BIT) {
		writel(val, pdata->ioaddr + reg);
		return;
	}

	if (pdata->config.flags & SMSC911X_USE_16BIT) {
		unsigned long flags;

		/* these two 16-bit writes must be performed consecutively, so
		 * must not be interrupted by our own ISR (which would start
		 * another read operation) */
		spin_lock_irqsave(&pdata->dev_lock, flags);
		writew(val & 0xFFFF, pdata->ioaddr + reg);
		writew((val >> 16) & 0xFFFF, pdata->ioaddr + reg + 2);
		spin_unlock_irqrestore(&pdata->dev_lock, flags);
		return;
	}

	BUG();
}