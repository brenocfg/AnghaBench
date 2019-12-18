#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ cxns_per_ctrl; } ;
struct beiscsi_hba {unsigned short* cid_array; scalar_t__ cid_free; TYPE_1__ params; int /*<<< orphan*/  avlbl_cids; } ;

/* Variables and functions */

__attribute__((used)) static void beiscsi_put_cid(struct beiscsi_hba *phba, unsigned short cid)
{
	phba->avlbl_cids++;
	phba->cid_array[phba->cid_free++] = cid;
	if (phba->cid_free == phba->params.cxns_per_ctrl)
		phba->cid_free = 0;
}