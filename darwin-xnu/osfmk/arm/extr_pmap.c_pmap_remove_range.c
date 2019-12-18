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
typedef  int /*<<< orphan*/  vm_map_address_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;

/* Variables and functions */
 int /*<<< orphan*/  PMAP_OPTIONS_REMOVE ; 
 int pmap_remove_range_options (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pmap_remove_range(
	pmap_t pmap,
	vm_map_address_t va,
	pt_entry_t *bpte,
	pt_entry_t *epte,
	uint32_t *rmv_cnt)
{
	return pmap_remove_range_options(pmap, va, bpte, epte, rmv_cnt,
					 PMAP_OPTIONS_REMOVE);
}