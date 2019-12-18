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
struct TYPE_7__ {size_t limit_entry; scalar_t__ sample_reg; scalar_t__ ackwidth; int /*<<< orphan*/  syncreg; int /*<<< orphan*/  period; int /*<<< orphan*/  offset; } ;
typedef  TYPE_2__ nsp32_target ;
struct TYPE_8__ {TYPE_1__* synct; } ;
typedef  TYPE_3__ nsp32_hw_data ;
struct TYPE_6__ {unsigned char period_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC_OFFSET ; 
 int /*<<< orphan*/  NSP32_DEBUG_SYNC ; 
 int /*<<< orphan*/  TO_SYNCREG (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsp32_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void nsp32_set_async(nsp32_hw_data *data, nsp32_target *target)
{
	unsigned char period = data->synct[target->limit_entry].period_num;

	target->offset     = ASYNC_OFFSET;
	target->period     = 0;
	target->syncreg    = TO_SYNCREG(period, ASYNC_OFFSET);
	target->ackwidth   = 0;
	target->sample_reg = 0;

	nsp32_dbg(NSP32_DEBUG_SYNC, "set async");
}