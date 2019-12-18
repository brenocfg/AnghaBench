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
typedef  scalar_t__ u8 ;
typedef  int u64 ;
struct ipz_adapter_handle {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  H_REGISTER_RPAGES ; 
 int ehca_plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int const,int const,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u64 hipz_h_register_rpage(const struct ipz_adapter_handle adapter_handle,
			  const u8 pagesize,
			  const u8 queue_type,
			  const u64 resource_handle,
			  const u64 logical_address_of_page,
			  u64 count)
{
	return ehca_plpar_hcall_norets(H_REGISTER_RPAGES,
				       adapter_handle.handle,      /* r4  */
				       (u64)queue_type | ((u64)pagesize) << 8,
				       /* r5  */
				       resource_handle,	           /* r6  */
				       logical_address_of_page,    /* r7  */
				       count,	                   /* r8  */
				       0, 0);
}