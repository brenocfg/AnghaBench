#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct be_queue_info {int id; } ;
struct TYPE_3__ {struct be_queue_info q; } ;
struct TYPE_4__ {TYPE_1__ mcc_obj; } ;
struct beiscsi_hba {scalar_t__ db_va; TYPE_2__ ctrl; } ;

/* Variables and functions */
 int DB_MCCQ_NUM_POSTED_SHIFT ; 
 scalar_t__ DB_MCCQ_OFFSET ; 
 int DB_MCCQ_RING_ID_MASK ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 

void be_mcc_notify(struct beiscsi_hba *phba)
{
	struct be_queue_info *mccq = &phba->ctrl.mcc_obj.q;
	u32 val = 0;

	val |= mccq->id & DB_MCCQ_RING_ID_MASK;
	val |= 1 << DB_MCCQ_NUM_POSTED_SHIFT;
	iowrite32(val, phba->db_va + DB_MCCQ_OFFSET);
}