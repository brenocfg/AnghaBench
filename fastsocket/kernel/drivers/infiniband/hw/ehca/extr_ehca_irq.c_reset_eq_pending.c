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
struct h_galpa {int dummy; } ;
struct TYPE_2__ {struct h_galpa kernel; } ;
struct ehca_cq {TYPE_1__ galpas; } ;

/* Variables and functions */
 int /*<<< orphan*/  CQTEMM_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cqx_ep ; 
 int /*<<< orphan*/  hipz_galpa_load (struct h_galpa,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hipz_galpa_store_cq (struct h_galpa,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void reset_eq_pending(struct ehca_cq *cq)
{
	u64 CQx_EP;
	struct h_galpa gal = cq->galpas.kernel;

	hipz_galpa_store_cq(gal, cqx_ep, 0x0);
	CQx_EP = hipz_galpa_load(gal, CQTEMM_OFFSET(cqx_ep));

	return;
}