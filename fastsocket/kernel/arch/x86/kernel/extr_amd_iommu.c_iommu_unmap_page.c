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
typedef  scalar_t__ u64 ;
struct protection_domain {int dummy; } ;

/* Variables and functions */
 scalar_t__* fetch_pte (struct protection_domain*,unsigned long,int) ; 

__attribute__((used)) static void iommu_unmap_page(struct protection_domain *dom,
			     unsigned long bus_addr, int map_size)
{
	u64 *pte = fetch_pte(dom, bus_addr, map_size);

	if (pte)
		*pte = 0;
}