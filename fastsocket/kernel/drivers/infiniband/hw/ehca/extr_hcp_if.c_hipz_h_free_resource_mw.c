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
struct ipz_adapter_handle {int /*<<< orphan*/  handle; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;
struct ehca_mw {TYPE_1__ ipz_mw_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  H_FREE_RESOURCE ; 
 int /*<<< orphan*/  ehca_plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u64 hipz_h_free_resource_mw(const struct ipz_adapter_handle adapter_handle,
			    const struct ehca_mw *mw)
{
	return ehca_plpar_hcall_norets(H_FREE_RESOURCE,
				       adapter_handle.handle,    /* r4 */
				       mw->ipz_mw_handle.handle, /* r5 */
				       0, 0, 0, 0, 0);
}