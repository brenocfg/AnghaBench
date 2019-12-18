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
typedef  int u8 ;
typedef  size_t u32 ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  dsptask_t ;
struct TYPE_3__ {size_t cipher; size_t latency; scalar_t__ workarea; int /*<<< orphan*/  dsp_task; } ;
typedef  TYPE_1__ card_block ;

/* Variables and functions */
 scalar_t__ CARD_ERROR_IOERROR ; 
 scalar_t__ CARD_ERROR_NOCARD ; 
 int CARD_STATUS_UNLOCKED ; 
 size_t EXI_CHANNEL_2 ; 
 scalar_t__ EXI_Probe (size_t) ; 
 int /*<<< orphan*/  EXI_Unlock (size_t) ; 
 size_t __card_dummylen () ; 
 int /*<<< orphan*/  __card_mountcallback (size_t,scalar_t__) ; 
 scalar_t__ __card_readarrayunlock (size_t,size_t,int /*<<< orphan*/ ,size_t,int) ; 
 scalar_t__ __card_readstatus (size_t,int*) ; 
 TYPE_1__* cardmap ; 
 size_t exnor (size_t,size_t) ; 
 int /*<<< orphan*/  tmp_buffer ; 

__attribute__((used)) static void __dsp_donecallback(dsptask_t *task)
{

	u8 status;
	s32 ret;
	u32 chn,len,key;
	u32 workarea,val;
	card_block *card = NULL;
	chn = 0;
	while(chn<EXI_CHANNEL_2) {
		card = &cardmap[chn];
		if(&card->dsp_task==task) break;
		chn++;
	}
	if(chn>=EXI_CHANNEL_2) return;

	workarea = (u32)card->workarea;
	workarea = ((workarea+47)&~0x1f);
	key = ((u32*)workarea)[8];

	val = (key^card->cipher)&~0xffff;
	len = __card_dummylen();
	if(__card_readarrayunlock(chn,val,tmp_buffer,len,1)<0) {
		EXI_Unlock(chn);
		__card_mountcallback(chn,CARD_ERROR_NOCARD);
		return;
	}

	val = exnor(card->cipher,((len+card->latency+4)<<3)+1);
	{
		u32 a,b,c,r1,r2,r3;
		a = (val<<23);
		b = (val<<15);
		c = (val<<7);
		r1 = (val^c);
		r2 = (b^r1);
		r3 = ~(a^r2);		//eqv(a,r2)
		r1 = (val|(r3>>31));
		card->cipher = r1;
	}

	val = ((key<<16)^card->cipher)&~0xffff;
	len = __card_dummylen();
	if(__card_readarrayunlock(chn,val,tmp_buffer,len,1)<0) {
		EXI_Unlock(chn);
		__card_mountcallback(chn,CARD_ERROR_NOCARD);
		return;
	}

	ret = __card_readstatus(chn,&status);
	if(EXI_Probe(chn)==0) {
		EXI_Unlock(chn);
		__card_mountcallback(chn,CARD_ERROR_NOCARD);
		return;
	}
	if(!ret && !(status&CARD_STATUS_UNLOCKED)) {
		EXI_Unlock(chn);
		ret = CARD_ERROR_IOERROR;
	}
	__card_mountcallback(chn,ret);
}