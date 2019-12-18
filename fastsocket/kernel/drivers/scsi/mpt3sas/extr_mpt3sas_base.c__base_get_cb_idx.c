#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct MPT3SAS_ADAPTER {int hi_priority_smid; int internal_smid; int hba_queue_depth; TYPE_2__* internal_lookup; TYPE_1__* hpr_lookup; TYPE_3__* scsi_lookup; } ;
struct TYPE_6__ {int cb_idx; } ;
struct TYPE_5__ {int cb_idx; } ;
struct TYPE_4__ {int cb_idx; } ;

/* Variables and functions */

__attribute__((used)) static u8
_base_get_cb_idx(struct MPT3SAS_ADAPTER *ioc, u16 smid)
{
	int i;
	u8 cb_idx;

	if (smid < ioc->hi_priority_smid) {
		i = smid - 1;
		cb_idx = ioc->scsi_lookup[i].cb_idx;
	} else if (smid < ioc->internal_smid) {
		i = smid - ioc->hi_priority_smid;
		cb_idx = ioc->hpr_lookup[i].cb_idx;
	} else if (smid <= ioc->hba_queue_depth) {
		i = smid - ioc->internal_smid;
		cb_idx = ioc->internal_lookup[i].cb_idx;
	} else
		cb_idx = 0xFF;
	return cb_idx;
}