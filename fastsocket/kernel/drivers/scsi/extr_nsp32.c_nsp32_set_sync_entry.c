#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned char ackwidth; unsigned char offset; unsigned char sample_reg; int /*<<< orphan*/  syncreg; } ;
typedef  TYPE_2__ nsp32_target ;
struct TYPE_8__ {TYPE_1__* synct; } ;
typedef  TYPE_3__ nsp32_hw_data ;
struct TYPE_6__ {unsigned char period_num; unsigned char ackwidth; unsigned char sample_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  NSP32_DEBUG_SYNC ; 
 unsigned char SAMPLING_ENABLE ; 
 int /*<<< orphan*/  TO_SYNCREG (unsigned char,unsigned char) ; 
 int /*<<< orphan*/  nsp32_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void nsp32_set_sync_entry(nsp32_hw_data *data,
				 nsp32_target  *target,
				 int            entry,
				 unsigned char  offset)
{
	unsigned char period, ackwidth, sample_rate;

	period      = data->synct[entry].period_num;
	ackwidth    = data->synct[entry].ackwidth;
	offset      = offset;
	sample_rate = data->synct[entry].sample_rate;

	target->syncreg    = TO_SYNCREG(period, offset);
	target->ackwidth   = ackwidth;
	target->offset     = offset;
	target->sample_reg = sample_rate | SAMPLING_ENABLE;

	nsp32_dbg(NSP32_DEBUG_SYNC, "set sync");
}