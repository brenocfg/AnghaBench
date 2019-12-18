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
typedef  int /*<<< orphan*/  u64 ;
struct sn_irq_info {int /*<<< orphan*/  irq_bridge; } ;
typedef  int nasid_t ;

/* Variables and functions */
 int NASID_GET (int /*<<< orphan*/ ) ; 
 int TIO_SWIN_WIDGETNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sn_irq_info*) ; 
 int /*<<< orphan*/  tiocx_intr_free (int,int,struct sn_irq_info*) ; 

void tiocx_irq_free(struct sn_irq_info *sn_irq_info)
{
	u64 bridge = (u64) sn_irq_info->irq_bridge;
	nasid_t nasid = NASID_GET(bridge);
	int widget;

	if (nasid & 1) {
		widget = TIO_SWIN_WIDGETNUM(bridge);
		tiocx_intr_free(nasid, widget, sn_irq_info);
		kfree(sn_irq_info);
	}
}