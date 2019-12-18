#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int major; int minor; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ sb_devc ;

/* Variables and functions */
 int /*<<< orphan*/  DDB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSP_DATA_AVAIL ; 
 int /*<<< orphan*/  DSP_READ ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  sb_dsp_command (TYPE_1__*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void dsp_get_vers(sb_devc * devc)
{
	int i;

	unsigned long   flags;

	DDB(printk("Entered dsp_get_vers()\n"));
	spin_lock_irqsave(&devc->lock, flags);
	devc->major = devc->minor = 0;
	sb_dsp_command(devc, 0xe1);	/* Get version */

	for (i = 100000; i; i--)
	{
		if (inb(DSP_DATA_AVAIL) & 0x80)
		{
			if (devc->major == 0)
				devc->major = inb(DSP_READ);
			else
			{
				devc->minor = inb(DSP_READ);
				break;
			}
		}
	}
	spin_unlock_irqrestore(&devc->lock, flags);
	DDB(printk("DSP version %d.%02d\n", devc->major, devc->minor));
}