#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t s32 ;
struct TYPE_3__ {scalar_t__ exi_idtime; int /*<<< orphan*/  exi_id; } ;
typedef  TYPE_1__ exibus_priv ;

/* Variables and functions */
 size_t EXI_CHANNEL_2 ; 
 size_t EXI_DEVICE_0 ; 
 int /*<<< orphan*/  EXI_Deselect (size_t) ; 
 int /*<<< orphan*/  EXI_Detach (size_t) ; 
 int /*<<< orphan*/  EXI_Imm (size_t,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t EXI_Lock (size_t,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EXI_READ ; 
 int /*<<< orphan*/  EXI_SPEED1MHZ ; 
 int EXI_Select (size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXI_Sync (size_t) ; 
 int /*<<< orphan*/  EXI_Unlock (size_t) ; 
 int /*<<< orphan*/  EXI_WRITE ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 scalar_t__ __exi_attach (size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ __exi_probe (size_t) ; 
 int /*<<< orphan*/ * __unlocked_handler ; 
 TYPE_1__* eximap ; 
 scalar_t__* last_exi_idtime ; 

s32 EXI_GetID(s32 nChn,s32 nDev,u32 *nId)
{
	u64 idtime = 0;
	s32 ret,lck;
	u32 reg,level;
	exibus_priv *exi = &eximap[nChn];

	if(nChn<EXI_CHANNEL_2 && nDev==EXI_DEVICE_0) {
		if(__exi_probe(nChn)==0) return 0;
		if(exi->exi_idtime==last_exi_idtime[nChn]) {
			*nId = exi->exi_id;
			return 1;
		}
		if(__exi_attach(nChn,NULL)==0) return 0;
		idtime = last_exi_idtime[nChn];
	}
	lck = 0;
	if(nChn<EXI_CHANNEL_2 && nDev==EXI_DEVICE_0) lck = 1;

	if(lck)  ret = EXI_Lock(nChn,nDev,__unlocked_handler);
	else ret = EXI_Lock(nChn,nDev,NULL);

	if(ret) {
		if(EXI_Select(nChn,nDev,EXI_SPEED1MHZ)==1) {
			reg = 0;
			EXI_Imm(nChn,&reg,2,EXI_WRITE,NULL);
			EXI_Sync(nChn);
			EXI_Imm(nChn,nId,4,EXI_READ,NULL);
			EXI_Sync(nChn);
			EXI_Deselect(nChn);
			EXI_Unlock(nChn);
		}
	}

	if(nChn<EXI_CHANNEL_2 && nDev==EXI_DEVICE_0) {
		ret = 0;
		EXI_Detach(nChn);

		_CPU_ISR_Disable(level);
		if(idtime==last_exi_idtime[nChn]) {
			exi->exi_idtime = idtime;
			exi->exi_id = *nId;
			ret = 1;
		}
		_CPU_ISR_Restore(level);
	}
	return ret;
}