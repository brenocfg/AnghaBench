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
typedef  int WORD ;
struct TYPE_2__ {scalar_t__ io; scalar_t__ base; int /*<<< orphan*/  DARF; scalar_t__ DARQ; } ;
typedef  scalar_t__ LPDAQD ;

/* Variables and functions */
 int DAQDS__size ; 
 scalar_t__ DAQDS_wSize ; 
 scalar_t__ DARQ_DATA_BUFF ; 
 int DAR_BUFF_SIZE ; 
 int /*<<< orphan*/  HPBLKSEL_0 ; 
 int /*<<< orphan*/  HPBLKSEL_1 ; 
 scalar_t__ HP_BLKS ; 
 scalar_t__ JQS_wHead ; 
 scalar_t__ JQS_wSize ; 
 scalar_t__ JQS_wTail ; 
 int PCTODSP_OFFSET (int) ; 
 TYPE_1__ dev ; 
 int /*<<< orphan*/  msnd_fifo_write_io (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  msnd_outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int readw (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static __inline__ int pack_DARQ_to_DARF(register int bank)
{
	register int size, timeout = 3;
	register WORD wTmp;
	LPDAQD DAQD;

	/* Increment the tail and check for queue wrap */
	wTmp = readw(dev.DARQ + JQS_wTail) + PCTODSP_OFFSET(DAQDS__size);
	if (wTmp > readw(dev.DARQ + JQS_wSize))
		wTmp = 0;
	while (wTmp == readw(dev.DARQ + JQS_wHead) && timeout--)
		udelay(1);
	writew(wTmp, dev.DARQ + JQS_wTail);

	/* Get our digital audio queue struct */
	DAQD = bank * DAQDS__size + dev.base + DARQ_DATA_BUFF;

	/* Get length of data */
	size = readw(DAQD + DAQDS_wSize);

	/* Read data from the head (unprotected bank 1 access okay
           since this is only called inside an interrupt) */
	msnd_outb(HPBLKSEL_1, dev.io + HP_BLKS);
	msnd_fifo_write_io(
		&dev.DARF,
		dev.base + bank * DAR_BUFF_SIZE,
		size);
	msnd_outb(HPBLKSEL_0, dev.io + HP_BLKS);

	return 1;
}