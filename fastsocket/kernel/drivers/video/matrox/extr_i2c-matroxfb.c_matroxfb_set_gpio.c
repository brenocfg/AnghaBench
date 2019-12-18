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
struct matrox_fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAC_XGENIOCTRL ; 
 int /*<<< orphan*/  DAC_XGENIODATA ; 
 int matroxfb_DAC_in (struct matrox_fb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  matroxfb_DAC_lock_irqsave (unsigned long) ; 
 int /*<<< orphan*/  matroxfb_DAC_out (struct matrox_fb_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  matroxfb_DAC_unlock_irqrestore (unsigned long) ; 

__attribute__((used)) static void matroxfb_set_gpio(struct matrox_fb_info* minfo, int mask, int val) {
	unsigned long flags;
	int v;

	matroxfb_DAC_lock_irqsave(flags);
	v = (matroxfb_DAC_in(minfo, DAC_XGENIOCTRL) & mask) | val;
	matroxfb_DAC_out(minfo, DAC_XGENIOCTRL, v);
	/* We must reset GENIODATA very often... XFree plays with this register */
	matroxfb_DAC_out(minfo, DAC_XGENIODATA, 0x00);
	matroxfb_DAC_unlock_irqrestore(flags);
}