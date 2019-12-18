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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  kernel; } ;
struct ehca_cq {TYPE_1__ galpas; } ;

/* Variables and functions */
 int /*<<< orphan*/  CQX_N0_GENERATE_SOLICITED_COMP_EVENT ; 
 int /*<<< orphan*/  EHCA_BMASK_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cqx_n0 ; 
 int /*<<< orphan*/  hipz_galpa_load_cq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hipz_galpa_store_cq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void hipz_set_cqx_n0(struct ehca_cq *cq, u32 value)
{
	u64 cqx_n0_reg;

	hipz_galpa_store_cq(cq->galpas.kernel, cqx_n0,
			    EHCA_BMASK_SET(CQX_N0_GENERATE_SOLICITED_COMP_EVENT,
					   value));
	cqx_n0_reg = hipz_galpa_load_cq(cq->galpas.kernel, cqx_n0);
}