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
typedef  int u32 ;
struct bfa_s {int dummy; } ;

/* Variables and functions */
 int BFI_MSIX_CT_MAX ; 

void
bfa_hwct_msix_getvecs(struct bfa_s *bfa, u32 *msix_vecs_bmap,
		 u32 *num_vecs, u32 *max_vec_bit)
{
	*msix_vecs_bmap = (1 << BFI_MSIX_CT_MAX) - 1;
	*max_vec_bit = (1 << (BFI_MSIX_CT_MAX - 1));
	*num_vecs = BFI_MSIX_CT_MAX;
}