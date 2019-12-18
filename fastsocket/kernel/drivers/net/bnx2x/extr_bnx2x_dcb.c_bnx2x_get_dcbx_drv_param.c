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
typedef  int /*<<< orphan*/  u32 ;
struct dcbx_features {int /*<<< orphan*/  ets; int /*<<< orphan*/  pfc; int /*<<< orphan*/  app; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnx2x_dcbx_get_ap_feature (struct bnx2x*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_dcbx_get_ets_feature (struct bnx2x*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_dcbx_get_pfc_feature (struct bnx2x*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_get_dcbx_drv_param(struct bnx2x *bp,
				     struct dcbx_features *features,
				     u32 error)
{
	bnx2x_dcbx_get_ap_feature(bp, &features->app, error);

	bnx2x_dcbx_get_pfc_feature(bp, &features->pfc, error);

	bnx2x_dcbx_get_ets_feature(bp, &features->ets, error);
}