#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct be_adapter {scalar_t__ db; } ;

/* Variables and functions */
 int DB_RQ_NUM_POSTED_SHIFT ; 
 scalar_t__ DB_RQ_OFFSET ; 
 int DB_RQ_RING_ID_MASK ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void be_rxq_notify(struct be_adapter *adapter, u16 qid, u16 posted)
{
	u32 val = 0;
	val |= qid & DB_RQ_RING_ID_MASK;
	val |= posted << DB_RQ_NUM_POSTED_SHIFT;

	wmb();
	iowrite32(val, adapter->db + DB_RQ_OFFSET);
}