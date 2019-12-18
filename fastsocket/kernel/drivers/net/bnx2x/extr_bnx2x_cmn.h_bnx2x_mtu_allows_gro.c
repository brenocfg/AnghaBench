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

/* Variables and functions */
 int ETH_MAX_TPA_HEADER_SIZE ; 
 int MAX_SKB_FRAGS ; 
 int SGE_PAGE_SIZE ; 
 int U_ETH_SGL_SIZE ; 

__attribute__((used)) static inline bool bnx2x_mtu_allows_gro(int mtu)
{
	/* gro frags per page */
	int fpp = SGE_PAGE_SIZE / (mtu - ETH_MAX_TPA_HEADER_SIZE);

	/*
	 * 1. Number of frags should not grow above MAX_SKB_FRAGS
	 * 2. Frag must fit the page
	 */
	return mtu <= SGE_PAGE_SIZE && (U_ETH_SGL_SIZE * fpp) <= MAX_SKB_FRAGS;
}