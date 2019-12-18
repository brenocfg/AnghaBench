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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ipz_qp_handle {int /*<<< orphan*/  handle; } ;
struct ipz_adapter_handle {int /*<<< orphan*/  handle; } ;
struct h_galpa {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  H_DEFINE_AQP0 ; 
 int /*<<< orphan*/  ehca_plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u64 hipz_h_define_aqp0(const struct ipz_adapter_handle adapter_handle,
		       const struct ipz_qp_handle qp_handle,
		       struct h_galpa gal,
		       u32 port)
{
	return ehca_plpar_hcall_norets(H_DEFINE_AQP0,
				       adapter_handle.handle, /* r4 */
				       qp_handle.handle,      /* r5 */
				       port,                  /* r6 */
				       0, 0, 0, 0);
}