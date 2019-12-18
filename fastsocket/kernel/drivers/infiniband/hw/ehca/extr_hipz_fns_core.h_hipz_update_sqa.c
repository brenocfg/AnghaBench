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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  kernel; } ;
struct ehca_qp {TYPE_1__ galpas; } ;

/* Variables and functions */
 int /*<<< orphan*/  EHCA_BMASK_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QPX_SQADDER ; 
 int /*<<< orphan*/  hipz_galpa_store_qp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qpx_sqa ; 

__attribute__((used)) static inline void hipz_update_sqa(struct ehca_qp *qp, u16 nr_wqes)
{
	/*  ringing doorbell :-) */
	hipz_galpa_store_qp(qp->galpas.kernel, qpx_sqa,
			    EHCA_BMASK_SET(QPX_SQADDER, nr_wqes));
}