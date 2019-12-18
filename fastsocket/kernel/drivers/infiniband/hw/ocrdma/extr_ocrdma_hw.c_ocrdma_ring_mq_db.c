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
typedef  int u32 ;
struct TYPE_6__ {scalar_t__ db; } ;
struct TYPE_4__ {int id; } ;
struct TYPE_5__ {TYPE_1__ sq; } ;
struct ocrdma_dev {TYPE_3__ nic_info; TYPE_2__ mq; } ;

/* Variables and functions */
 scalar_t__ OCRDMA_DB_MQ_OFFSET ; 
 int OCRDMA_MQ_ID_MASK ; 
 int OCRDMA_MQ_NUM_MQE_SHIFT ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 

__attribute__((used)) static void ocrdma_ring_mq_db(struct ocrdma_dev *dev)
{
	u32 val = 0;

	val |= dev->mq.sq.id & OCRDMA_MQ_ID_MASK;
	val |= 1 << OCRDMA_MQ_NUM_MQE_SHIFT;
	iowrite32(val, dev->nic_info.db + OCRDMA_DB_MQ_OFFSET);
}