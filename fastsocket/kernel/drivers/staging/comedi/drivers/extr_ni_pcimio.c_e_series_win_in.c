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
typedef  int /*<<< orphan*/  uint16_t ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  window_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  Window_Address ; 
 int /*<<< orphan*/  Window_Data ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  ni_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_writew (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static uint16_t e_series_win_in(struct comedi_device *dev, int reg)
{
	unsigned long flags;
	uint16_t ret;

	spin_lock_irqsave(&devpriv->window_lock, flags);
	ni_writew(reg, Window_Address);
	ret = ni_readw(Window_Data);
	spin_unlock_irqrestore(&devpriv->window_lock, flags);

	return ret;
}