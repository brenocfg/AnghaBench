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
struct TYPE_6__ {TYPE_1__* iop; } ;
struct TYPE_5__ {TYPE_3__ itl; } ;
struct hptiop_hba {TYPE_2__ u; } ;
struct TYPE_4__ {int /*<<< orphan*/  outbound_intstatus; int /*<<< orphan*/  outbound_queue; int /*<<< orphan*/  inbound_queue; } ;

/* Variables and functions */
 int IOPMU_QUEUE_EMPTY ; 
 int /*<<< orphan*/  msleep (int) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iop_wait_ready_itl(struct hptiop_hba *hba, u32 millisec)
{
	u32 req = 0;
	int i;

	for (i = 0; i < millisec; i++) {
		req = readl(&hba->u.itl.iop->inbound_queue);
		if (req != IOPMU_QUEUE_EMPTY)
			break;
		msleep(1);
	}

	if (req != IOPMU_QUEUE_EMPTY) {
		writel(req, &hba->u.itl.iop->outbound_queue);
		readl(&hba->u.itl.iop->outbound_intstatus);
		return 0;
	}

	return -1;
}