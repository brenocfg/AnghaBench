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
struct e100_serial {unsigned char* ioport; int line; int forced_eop; } ;
struct TYPE_2__ {int /*<<< orphan*/  timeout_flush_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_LOG (int,char*,unsigned char) ; 
 int /*<<< orphan*/  FORCE_EOP (struct e100_serial*) ; 
 int /*<<< orphan*/  PROCSTAT (int /*<<< orphan*/ ) ; 
 size_t REG_DATA ; 
 size_t REG_STATUS ; 
 unsigned char SER_DATA_AVAIL_MASK ; 
 unsigned char SER_ERROR_MASK ; 
 int /*<<< orphan*/  START_FLUSH_FAST_TIMER (struct e100_serial*,char*) ; 
 int /*<<< orphan*/  TIMERD (int /*<<< orphan*/ ) ; 
 TYPE_1__* ser_stat ; 

__attribute__((used)) static int force_eop_if_needed(struct e100_serial *info)
{
	/* We check data_avail bit to determine if data has
	 * arrived since last time
	 */
	unsigned char rstat = info->ioport[REG_STATUS];

	/* error or datavail? */
	if (rstat & SER_ERROR_MASK) {
		/* Some error has occurred. If there has been valid data, an
		 * EOP interrupt will be made automatically. If no data, the
		 * normal ser_interrupt should be enabled and handle it.
		 * So do nothing!
		 */
		DEBUG_LOG(info->line, "timeout err: rstat 0x%03X\n",
		          rstat | (info->line << 8));
		return 0;
	}

	if (rstat & SER_DATA_AVAIL_MASK) {
		/* Ok data, no error, count it */
		TIMERD(DEBUG_LOG(info->line, "timeout: rstat 0x%03X\n",
		          rstat | (info->line << 8)));
		/* Read data to clear status flags */
		(void)info->ioport[REG_DATA];

		info->forced_eop = 0;
		START_FLUSH_FAST_TIMER(info, "magic");
		return 0;
	}

	/* hit the timeout, force an EOP for the input
	 * dma channel if we haven't already
	 */
	if (!info->forced_eop) {
		info->forced_eop = 1;
		PROCSTAT(ser_stat[info->line].timeout_flush_cnt++);
		TIMERD(DEBUG_LOG(info->line, "timeout EOP %i\n", info->line));
		FORCE_EOP(info);
	}

	return 1;
}