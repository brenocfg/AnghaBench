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
struct TYPE_7__ {int limit_entry; } ;
typedef  TYPE_2__ nsp32_target ;
struct TYPE_8__ {int syncnum; TYPE_1__* synct; } ;
typedef  TYPE_3__ nsp32_hw_data ;
struct TYPE_6__ {unsigned char start_period; unsigned char end_period; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  nsp32_msg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int nsp32_search_period_entry(nsp32_hw_data *data,
				     nsp32_target  *target,
				     unsigned char  period)
{
	int i;

	if (target->limit_entry >= data->syncnum) {
		nsp32_msg(KERN_ERR, "limit_entry exceeds syncnum!");
		target->limit_entry = 0;
	}

	for (i = target->limit_entry; i < data->syncnum; i++) {
		if (period >= data->synct[i].start_period &&
		    period <= data->synct[i].end_period) {
				break;
		}
	}

	/*
	 * Check given period value is over the sync_table value.
	 * If so, return max value.
	 */
	if (i == data->syncnum) {
		i = -1;
	}

	return i;
}