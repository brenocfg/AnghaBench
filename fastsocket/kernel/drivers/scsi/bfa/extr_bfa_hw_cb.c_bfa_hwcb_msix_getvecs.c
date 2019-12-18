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
struct bfa_s {int /*<<< orphan*/  ioc; } ;

/* Variables and functions */
 int __HFN_INT_CPE_Q0 ; 
 int __HFN_INT_CPE_Q1 ; 
 int __HFN_INT_CPE_Q2 ; 
 int __HFN_INT_CPE_Q3 ; 
 int __HFN_INT_CPE_Q4 ; 
 int __HFN_INT_CPE_Q5 ; 
 int __HFN_INT_CPE_Q6 ; 
 int __HFN_INT_CPE_Q7 ; 
 int __HFN_INT_ERR_EMC ; 
 int __HFN_INT_ERR_LPU0 ; 
 int __HFN_INT_ERR_LPU1 ; 
 int __HFN_INT_ERR_PSS ; 
 int __HFN_INT_MBOX_LPU0 ; 
 int __HFN_INT_MBOX_LPU1 ; 
 int __HFN_INT_RME_Q0 ; 
 int __HFN_INT_RME_Q1 ; 
 int __HFN_INT_RME_Q2 ; 
 int __HFN_INT_RME_Q3 ; 
 int __HFN_INT_RME_Q4 ; 
 int __HFN_INT_RME_Q5 ; 
 int __HFN_INT_RME_Q6 ; 
 int __HFN_INT_RME_Q7 ; 
 int __HFN_NUMINTS ; 
 scalar_t__ bfa_ioc_pcifn (int /*<<< orphan*/ *) ; 

void
bfa_hwcb_msix_getvecs(struct bfa_s *bfa, u32 *msix_vecs_bmap,
		 u32 *num_vecs, u32 *max_vec_bit)
{
#define __HFN_NUMINTS	13
	if (bfa_ioc_pcifn(&bfa->ioc) == 0) {
		*msix_vecs_bmap = (__HFN_INT_CPE_Q0 | __HFN_INT_CPE_Q1 |
				   __HFN_INT_CPE_Q2 | __HFN_INT_CPE_Q3 |
				   __HFN_INT_RME_Q0 | __HFN_INT_RME_Q1 |
				   __HFN_INT_RME_Q2 | __HFN_INT_RME_Q3 |
				   __HFN_INT_MBOX_LPU0);
		*max_vec_bit = __HFN_INT_MBOX_LPU0;
	} else {
		*msix_vecs_bmap = (__HFN_INT_CPE_Q4 | __HFN_INT_CPE_Q5 |
				   __HFN_INT_CPE_Q6 | __HFN_INT_CPE_Q7 |
				   __HFN_INT_RME_Q4 | __HFN_INT_RME_Q5 |
				   __HFN_INT_RME_Q6 | __HFN_INT_RME_Q7 |
				   __HFN_INT_MBOX_LPU1);
		*max_vec_bit = __HFN_INT_MBOX_LPU1;
	}

	*msix_vecs_bmap |= (__HFN_INT_ERR_EMC | __HFN_INT_ERR_LPU0 |
			    __HFN_INT_ERR_LPU1 | __HFN_INT_ERR_PSS);
	*num_vecs = __HFN_NUMINTS;
}