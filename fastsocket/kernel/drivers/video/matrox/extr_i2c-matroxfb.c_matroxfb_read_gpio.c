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
 int /*<<< orphan*/  DAC_XGENIODATA ; 
 int matroxfb_DAC_in (struct matrox_fb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  matroxfb_DAC_lock_irqsave (unsigned long) ; 
 int /*<<< orphan*/  matroxfb_DAC_unlock_irqrestore (unsigned long) ; 

__attribute__((used)) static int matroxfb_read_gpio(struct matrox_fb_info* minfo) {
	unsigned long flags;
	int v;

	matroxfb_DAC_lock_irqsave(flags);
	v = matroxfb_DAC_in(minfo, DAC_XGENIODATA);
	matroxfb_DAC_unlock_irqrestore(flags);
	return v;
}