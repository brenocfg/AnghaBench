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
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ CNIC_LOADED (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_int_disable_sync (struct bnx2x*,int) ; 
 int /*<<< orphan*/  bnx2x_napi_disable (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_napi_disable_cnic (struct bnx2x*) ; 

void bnx2x_netif_stop(struct bnx2x *bp, int disable_hw)
{
	bnx2x_int_disable_sync(bp, disable_hw);
	bnx2x_napi_disable(bp);
	if (CNIC_LOADED(bp))
		bnx2x_napi_disable_cnic(bp);
}