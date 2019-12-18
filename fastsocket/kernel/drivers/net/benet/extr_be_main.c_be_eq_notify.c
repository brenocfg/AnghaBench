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
struct be_adapter {scalar_t__ db; scalar_t__ eeh_error; } ;

/* Variables and functions */
 int DB_EQ_CLR_SHIFT ; 
 int DB_EQ_EVNT_SHIFT ; 
 int DB_EQ_NUM_POPPED_SHIFT ; 
 scalar_t__ DB_EQ_OFFSET ; 
 int DB_EQ_REARM_SHIFT ; 
 int DB_EQ_RING_ID_EXT_MASK ; 
 int DB_EQ_RING_ID_EXT_MASK_SHIFT ; 
 int DB_EQ_RING_ID_MASK ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 

__attribute__((used)) static void be_eq_notify(struct be_adapter *adapter, u16 qid,
		bool arm, bool clear_int, u16 num_popped)
{
	u32 val = 0;
	val |= qid & DB_EQ_RING_ID_MASK;
	val |= ((qid & DB_EQ_RING_ID_EXT_MASK) <<
			DB_EQ_RING_ID_EXT_MASK_SHIFT);

	if (adapter->eeh_error)
		return;

	if (arm)
		val |= 1 << DB_EQ_REARM_SHIFT;
	if (clear_int)
		val |= 1 << DB_EQ_CLR_SHIFT;
	val |= 1 << DB_EQ_EVNT_SHIFT;
	val |= num_popped << DB_EQ_NUM_POPPED_SHIFT;
	iowrite32(val, adapter->db + DB_EQ_OFFSET);
}