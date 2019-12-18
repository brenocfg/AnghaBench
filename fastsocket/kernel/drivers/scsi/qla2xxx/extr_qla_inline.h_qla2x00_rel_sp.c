#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  srb_t ;
struct TYPE_6__ {TYPE_1__* hw; } ;
typedef  TYPE_2__ scsi_qla_host_t ;
struct TYPE_5__ {int /*<<< orphan*/  srb_mempool; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLA_VHA_MARK_NOT_BUSY (TYPE_2__*) ; 
 int /*<<< orphan*/  mempool_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
qla2x00_rel_sp(scsi_qla_host_t *vha, srb_t *sp)
{
	mempool_free(sp, vha->hw->srb_mempool);
	QLA_VHA_MARK_NOT_BUSY(vha);
}