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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct ipz_eq_handle {int /*<<< orphan*/  handle; } ;
struct ipz_adapter_handle {int dummy; } ;
struct ehca_pfeq {int dummy; } ;

/* Variables and functions */
 int H_PARAMETER ; 
 int /*<<< orphan*/  ehca_gen_err (char*,int const) ; 
 int hipz_h_register_rpage (struct ipz_adapter_handle const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int const,int const) ; 

u64 hipz_h_register_rpage_eq(const struct ipz_adapter_handle adapter_handle,
			     const struct ipz_eq_handle eq_handle,
			     struct ehca_pfeq *pfeq,
			     const u8 pagesize,
			     const u8 queue_type,
			     const u64 logical_address_of_page,
			     const u64 count)
{
	if (count != 1) {
		ehca_gen_err("Ppage counter=%llx", count);
		return H_PARAMETER;
	}
	return hipz_h_register_rpage(adapter_handle,
				     pagesize,
				     queue_type,
				     eq_handle.handle,
				     logical_address_of_page, count);
}