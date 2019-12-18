#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
struct TYPE_3__ {scalar_t__ DAPQ; scalar_t__ base; int /*<<< orphan*/  DAPF; int /*<<< orphan*/  lock; } ;
typedef  scalar_t__ LPDAQD ;

/* Variables and functions */
 scalar_t__ DAPQ_DATA_BUFF ; 
 int DAP_BUFF_SIZE ; 
 int DAQDS__size ; 
 scalar_t__ DAQDS_wSize ; 
 int /*<<< orphan*/  HDEX_PLAY_START ; 
 scalar_t__ JQS_wHead ; 
 scalar_t__ JQS_wTail ; 
 int PCTODSP_OFFSET (int) ; 
 TYPE_1__ dev ; 
 int msnd_fifo_read_io (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  msnd_send_dsp_cmd (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int readw (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static __inline__ int pack_DAPF_to_DAPQ(register int start)
{
	register WORD DAPQ_tail;
	register int protect = start, nbanks = 0;
	LPDAQD DAQD;

	DAPQ_tail = readw(dev.DAPQ + JQS_wTail);
	while (DAPQ_tail != readw(dev.DAPQ + JQS_wHead) || start) {
		register int bank_num = DAPQ_tail / PCTODSP_OFFSET(DAQDS__size);
		register int n;
		unsigned long flags;

		/* Write the data to the new tail */
		if (protect) {
			/* Critical section: protect fifo in non-interrupt */
			spin_lock_irqsave(&dev.lock, flags);
			n = msnd_fifo_read_io(
				&dev.DAPF,
				dev.base + bank_num * DAP_BUFF_SIZE,
				DAP_BUFF_SIZE);
			spin_unlock_irqrestore(&dev.lock, flags);
		} else {
			n = msnd_fifo_read_io(
				&dev.DAPF,
				dev.base + bank_num * DAP_BUFF_SIZE,
				DAP_BUFF_SIZE);
		}
		if (!n)
			break;

		if (start)
			start = 0;

		/* Get our digital audio queue struct */
		DAQD = bank_num * DAQDS__size + dev.base + DAPQ_DATA_BUFF;

		/* Write size of this bank */
		writew(n, DAQD + DAQDS_wSize);
		++nbanks;

		/* Then advance the tail */
		DAPQ_tail = (++bank_num % 3) * PCTODSP_OFFSET(DAQDS__size);
		writew(DAPQ_tail, dev.DAPQ + JQS_wTail);
		/* Tell the DSP to play the bank */
		msnd_send_dsp_cmd(&dev, HDEX_PLAY_START);
	}
	return nbanks;
}