#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct spu_state {int* spu_chnlcnt_RW; int* spu_chnldata_RW; TYPE_2__* lscsa; } ;
struct spu {int dummy; } ;
struct TYPE_3__ {int* slot; } ;
struct TYPE_4__ {TYPE_1__ decr_status; } ;

/* Variables and functions */
 int SPU_DECR_STATUS_WRAPPED ; 

__attribute__((used)) static inline void restore_decr_wrapped(struct spu_state *csa, struct spu *spu)
{
	/* Restore, Step 58:
	 *     If the status of the CSA software decrementer
	 *     "wrapped" flag is set, OR in a '1' to
	 *     CSA.SPU_Event_Status[Tm].
	 */
	if (!(csa->lscsa->decr_status.slot[0] & SPU_DECR_STATUS_WRAPPED))
		return;

	if ((csa->spu_chnlcnt_RW[0] == 0) &&
	    (csa->spu_chnldata_RW[1] & 0x20) &&
	    !(csa->spu_chnldata_RW[0] & 0x20))
		csa->spu_chnlcnt_RW[0] = 1;

	csa->spu_chnldata_RW[0] |= 0x20;
}