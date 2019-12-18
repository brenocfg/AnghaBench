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
struct fc_fcp_pkt {int /*<<< orphan*/  lp; int /*<<< orphan*/  ref_cnt; } ;
struct fc_fcp_internal {int /*<<< orphan*/  scsi_pkt_pool; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 struct fc_fcp_internal* fc_get_scsi_internal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct fc_fcp_pkt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fc_fcp_pkt_release(struct fc_fcp_pkt *fsp)
{
	if (atomic_dec_and_test(&fsp->ref_cnt)) {
		struct fc_fcp_internal *si = fc_get_scsi_internal(fsp->lp);

		mempool_free(fsp, si->scsi_pkt_pool);
	}
}