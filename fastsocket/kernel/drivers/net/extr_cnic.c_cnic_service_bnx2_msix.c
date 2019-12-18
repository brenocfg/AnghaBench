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
struct cnic_local {int last_status_idx; int int_num; } ;
struct cnic_dev {struct cnic_local* cnic_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2_PCICFG_INT_ACK_CMD ; 
 int BNX2_PCICFG_INT_ACK_CMD_INDEX_VALID ; 
 int /*<<< orphan*/  CNIC_WR (struct cnic_dev*,int /*<<< orphan*/ ,int) ; 
 int cnic_service_bnx2_queues (struct cnic_dev*) ; 

__attribute__((used)) static void cnic_service_bnx2_msix(unsigned long data)
{
	struct cnic_dev *dev = (struct cnic_dev *) data;
	struct cnic_local *cp = dev->cnic_priv;

	cp->last_status_idx = cnic_service_bnx2_queues(dev);

	CNIC_WR(dev, BNX2_PCICFG_INT_ACK_CMD, cp->int_num |
		BNX2_PCICFG_INT_ACK_CMD_INDEX_VALID | cp->last_status_idx);
}