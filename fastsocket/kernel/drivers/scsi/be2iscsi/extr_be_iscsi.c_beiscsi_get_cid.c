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
struct beiscsi_hba {unsigned short* cid_array; scalar_t__ cid_alloc; int /*<<< orphan*/  avlbl_cids; TYPE_1__ params; } ;

/* Variables and functions */

__attribute__((used)) static int beiscsi_get_cid(struct beiscsi_hba *phba)
{
	unsigned short cid = 0xFFFF;

	if (!phba->avlbl_cids)
		return cid;

	cid = phba->cid_array[phba->cid_alloc++];
	if (phba->cid_alloc == phba->params.cxns_per_ctrl)
		phba->cid_alloc = 0;
	phba->avlbl_cids--;
	return cid;
}