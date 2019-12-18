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
struct cnic_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ BNX2_COM_SCRATCH ; 
 scalar_t__ BNX2_CP_SCRATCH ; 
 int /*<<< orphan*/  KCQ_CID ; 
 int /*<<< orphan*/  KWQ_CID ; 
 int /*<<< orphan*/  cnic_disable_bnx2_int_sync (struct cnic_dev*) ; 
 int /*<<< orphan*/  cnic_free_irq (struct cnic_dev*) ; 
 int /*<<< orphan*/  cnic_free_resc (struct cnic_dev*) ; 
 int /*<<< orphan*/  cnic_init_context (struct cnic_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cnic_reg_wr_ind (struct cnic_dev*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cnic_setup_5709_context (struct cnic_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cnic_stop_bnx2_hw(struct cnic_dev *dev)
{
	cnic_disable_bnx2_int_sync(dev);

	cnic_reg_wr_ind(dev, BNX2_CP_SCRATCH + 0x20, 0);
	cnic_reg_wr_ind(dev, BNX2_COM_SCRATCH + 0x20, 0);

	cnic_init_context(dev, KWQ_CID);
	cnic_init_context(dev, KCQ_CID);

	cnic_setup_5709_context(dev, 0);
	cnic_free_irq(dev);

	cnic_free_resc(dev);
}