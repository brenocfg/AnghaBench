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
struct spu_state {scalar_t__* spu_chnlcnt_RW; scalar_t__* spu_chnldata_RW; } ;
struct spu {int dummy; } ;

/* Variables and functions */
 scalar_t__ MFC_LLR_LOST_EVENT ; 

__attribute__((used)) static inline void set_llr_event(struct spu_state *csa, struct spu *spu)
{
	u64 ch0_cnt, ch0_data;
	u64 ch1_data;

	/* Restore, Step 57:
	 *    Set the Lock Line Reservation Lost Event by:
	 *      1. OR CSA.SPU_Event_Status with bit 21 (Lr) set to 1.
	 *      2. If CSA.SPU_Channel_0_Count=0 and
	 *         CSA.SPU_Wr_Event_Mask[Lr]=1 and
	 *         CSA.SPU_Event_Status[Lr]=0 then set
	 *         CSA.SPU_Event_Status_Count=1.
	 */
	ch0_cnt = csa->spu_chnlcnt_RW[0];
	ch0_data = csa->spu_chnldata_RW[0];
	ch1_data = csa->spu_chnldata_RW[1];
	csa->spu_chnldata_RW[0] |= MFC_LLR_LOST_EVENT;
	if ((ch0_cnt == 0) && !(ch0_data & MFC_LLR_LOST_EVENT) &&
	    (ch1_data & MFC_LLR_LOST_EVENT)) {
		csa->spu_chnlcnt_RW[0] = 1;
	}
}