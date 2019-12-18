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
struct saa7134_dev {int nosignal; int automute; TYPE_1__* mops; scalar_t__ ctl_automute; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* signal_change ) (struct saa7134_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SAA7134_STATUS_VIDEO1 ; 
 int /*<<< orphan*/  SAA7134_STATUS_VIDEO2 ; 
 int /*<<< orphan*/  SAA7134_SYNC_CTRL ; 
 int /*<<< orphan*/  dprintk (char*,char*,char*,char const*) ; 
 int /*<<< orphan*/  noninterlaced ; 
 int /*<<< orphan*/  saa7134_tvaudio_do_scan (struct saa7134_dev*) ; 
 int /*<<< orphan*/  saa7134_tvaudio_setmute (struct saa7134_dev*) ; 
 int /*<<< orphan*/  saa_clearb (int /*<<< orphan*/ ,int) ; 
 int saa_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa_setb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct saa7134_dev*) ; 

void saa7134_irq_video_signalchange(struct saa7134_dev *dev)
{
	static const char *st[] = {
		"(no signal)", "NTSC", "PAL", "SECAM" };
	u32 st1,st2;

	st1 = saa_readb(SAA7134_STATUS_VIDEO1);
	st2 = saa_readb(SAA7134_STATUS_VIDEO2);
	dprintk("DCSDT: pll: %s, sync: %s, norm: %s\n",
		(st1 & 0x40) ? "not locked" : "locked",
		(st2 & 0x40) ? "no"         : "yes",
		st[st1 & 0x03]);
	dev->nosignal = (st1 & 0x40) || (st2 & 0x40)  || !(st2 & 0x1);

	if (dev->nosignal) {
		/* no video signal -> mute audio */
		if (dev->ctl_automute)
			dev->automute = 1;
		saa7134_tvaudio_setmute(dev);
	} else {
		/* wake up tvaudio audio carrier scan thread */
		saa7134_tvaudio_do_scan(dev);
	}

	if ((st2 & 0x80) && !noninterlaced && !dev->nosignal)
		saa_clearb(SAA7134_SYNC_CTRL, 0x20);
	else
		saa_setb(SAA7134_SYNC_CTRL, 0x20);

	if (dev->mops && dev->mops->signal_change)
		dev->mops->signal_change(dev);
}