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
struct fc_lport {int dummy; } ;
struct TYPE_2__ {unsigned long data; } ;
struct fc_fcp_pkt {int /*<<< orphan*/  scsi_pkt_lock; int /*<<< orphan*/  list; TYPE_1__ timer; int /*<<< orphan*/  ref_cnt; int /*<<< orphan*/  xfer_ddp; struct fc_lport* lp; } ;
struct fc_fcp_internal {int /*<<< orphan*/  scsi_pkt_pool; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  FC_XID_UNKNOWN ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct fc_fcp_internal* fc_get_scsi_internal (struct fc_lport*) ; 
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 
 struct fc_fcp_pkt* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct fc_fcp_pkt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct fc_fcp_pkt *fc_fcp_pkt_alloc(struct fc_lport *lport, gfp_t gfp)
{
	struct fc_fcp_internal *si = fc_get_scsi_internal(lport);
	struct fc_fcp_pkt *fsp;

	fsp = mempool_alloc(si->scsi_pkt_pool, gfp);
	if (fsp) {
		memset(fsp, 0, sizeof(*fsp));
		fsp->lp = lport;
		fsp->xfer_ddp = FC_XID_UNKNOWN;
		atomic_set(&fsp->ref_cnt, 1);
		init_timer(&fsp->timer);
		fsp->timer.data = (unsigned long)fsp;
		INIT_LIST_HEAD(&fsp->list);
		spin_lock_init(&fsp->scsi_pkt_lock);
	}
	return fsp;
}