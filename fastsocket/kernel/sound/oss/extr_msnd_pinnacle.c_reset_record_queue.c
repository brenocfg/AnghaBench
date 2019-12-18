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
struct TYPE_2__ {int last_recbank; int rec_sample_size; int rec_channels; int rec_sample_rate; scalar_t__ base; int /*<<< orphan*/  lock; scalar_t__ io; scalar_t__ DARQ; } ;
typedef  scalar_t__ LPDAQD ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int DAQDS__size ; 
 scalar_t__ DAQDS_wChannels ; 
 scalar_t__ DAQDS_wFlags ; 
 scalar_t__ DAQDS_wFormat ; 
 scalar_t__ DAQDS_wIntMsg ; 
 scalar_t__ DAQDS_wSampleRate ; 
 scalar_t__ DAQDS_wSampleSize ; 
 scalar_t__ DAQDS_wSize ; 
 scalar_t__ DAQDS_wStart ; 
 scalar_t__ DARQ_DATA_BUFF ; 
 int DAR_BUFF_SIZE ; 
 int HIMT_RECORD_DONE ; 
 int /*<<< orphan*/  HPBLKSEL_0 ; 
 int /*<<< orphan*/  HPBLKSEL_1 ; 
 scalar_t__ HP_BLKS ; 
 scalar_t__ JQS_wHead ; 
 scalar_t__ JQS_wTail ; 
 int PCTODSP_BASED (int /*<<< orphan*/ ) ; 
 int PCTODSP_OFFSET (int) ; 
 TYPE_1__ dev ; 
 int /*<<< orphan*/  memset_io (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msnd_outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static void reset_record_queue(void)
{
	int n;
	LPDAQD lpDAQ;
	unsigned long flags;

	dev.last_recbank = 2;
	writew(PCTODSP_OFFSET(0 * DAQDS__size), dev.DARQ + JQS_wHead);
	writew(PCTODSP_OFFSET(dev.last_recbank * DAQDS__size), dev.DARQ + JQS_wTail);

	/* Critical section: bank 1 access */
	spin_lock_irqsave(&dev.lock, flags);
	msnd_outb(HPBLKSEL_1, dev.io + HP_BLKS);
	memset_io(dev.base, 0, DAR_BUFF_SIZE * 3);
	msnd_outb(HPBLKSEL_0, dev.io + HP_BLKS);
	spin_unlock_irqrestore(&dev.lock, flags);

	for (n = 0, lpDAQ = dev.base + DARQ_DATA_BUFF; n < 3; ++n, lpDAQ += DAQDS__size) {
		writew(PCTODSP_BASED((DWORD)(DAR_BUFF_SIZE * n)) + 0x4000, lpDAQ + DAQDS_wStart);
		writew(DAR_BUFF_SIZE, lpDAQ + DAQDS_wSize);
		writew(1, lpDAQ + DAQDS_wFormat);
		writew(dev.rec_sample_size, lpDAQ + DAQDS_wSampleSize);
		writew(dev.rec_channels, lpDAQ + DAQDS_wChannels);
		writew(dev.rec_sample_rate, lpDAQ + DAQDS_wSampleRate);
		writew(HIMT_RECORD_DONE * 0x100 + n, lpDAQ + DAQDS_wIntMsg);
		writew(n, lpDAQ + DAQDS_wFlags);
	}
}