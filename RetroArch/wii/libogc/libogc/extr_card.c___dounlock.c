#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  size_t s32 ;
struct TYPE_5__ {int prio; int iram_len; int iram_addr; int init_vec; int /*<<< orphan*/  done_cb; int /*<<< orphan*/  init_cb; int /*<<< orphan*/ * req_cb; int /*<<< orphan*/ * res_cb; int /*<<< orphan*/ * iram_maddr; } ;
struct TYPE_4__ {int* workarea; int cipher; TYPE_3__ dsp_task; } ;
typedef  TYPE_1__ card_block ;

/* Variables and functions */
 size_t CARD_ERROR_NOCARD ; 
 size_t CARD_ERROR_READY ; 
 int /*<<< orphan*/  DCFlushRange (int*,int) ; 
 int /*<<< orphan*/  DCInvalidateRange (int*,int) ; 
 int /*<<< orphan*/  DSP_AddTask (TYPE_3__*) ; 
 scalar_t__ MEM_VIRTUAL_TO_PHYSICAL (int /*<<< orphan*/ ) ; 
 int __card_dummylen () ; 
 int __card_initval () ; 
 scalar_t__ __card_readarrayunlock (size_t,int,scalar_t__,int,int) ; 
 int /*<<< orphan*/  __dsp_donecallback ; 
 int /*<<< orphan*/  __dsp_initcallback ; 
 int /*<<< orphan*/  _cardunlockdata ; 
 int bitrev (int) ; 
 TYPE_1__* cardmap ; 
 int exnor (int,int) ; 
 int exnor_1st (int,int) ; 
 scalar_t__ tmp_buffer ; 

__attribute__((used)) static s32 __dounlock(s32 chn,u32 *key)
{
	u32 array_addr,len,val;
	u32 a,b,c,d,e;
	card_block *card = &cardmap[chn];
	u32 *workarea = card->workarea;
	u32 *cipher1 = (u32*)(((u32)card->workarea+47)&~31);
	u32 *cipher2 = &cipher1[8];
	array_addr = __card_initval();
	len = __card_dummylen();

	if(__card_readarrayunlock(chn,array_addr,tmp_buffer,len,0)<0) return CARD_ERROR_NOCARD;

	val = exnor_1st(array_addr,(len<<3)+1);
	{
		u32 a,b,c,r1,r2,r3;
		a = (val>>23);
		b = (val>>15);
		c = (val>>7);
		r1 = (val^c);
		r2 = (b^r1);
		r3 = ~(a^r2);		//eqv(a,r2)
		r1 = (val|(r3<<31));
		card->cipher = r1;
	}
	card->cipher = bitrev(card->cipher);

	array_addr = 0;
	len = __card_dummylen();
	if(__card_readarrayunlock(chn,array_addr,tmp_buffer,len+20,1)<0) return CARD_ERROR_NOCARD;

	a = ((u32*)tmp_buffer)[0];
	b = ((u32*)tmp_buffer)[1];
	c = ((u32*)tmp_buffer)[2];
	d = ((u32*)tmp_buffer)[3];
	e = ((u32*)tmp_buffer)[4];

	a = a^card->cipher;
	val = exnor(card->cipher,32);
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

	b = b^card->cipher;
	val = exnor(card->cipher,32);
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

	c = c^card->cipher;
	val = exnor(card->cipher,32);
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

	d = d^card->cipher;
	val = exnor(card->cipher,32);
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

	e = e^card->cipher;
	val = exnor(card->cipher,(len<<3));
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

	val = exnor(card->cipher,33);
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

	cipher1[0] = d;
	cipher1[1] = e;
	workarea[0] = (u32)cipher1;
	workarea[1] = 8;
#ifdef HW_RVL
	workarea[2] = 0x10000000; // use MEM2 base
#else
	workarea[2] = 0; // use ARAM base
#endif
	workarea[3] = (u32)cipher2;
	DCFlushRange(cipher1,8);
	DCInvalidateRange(cipher2,4);
	DCFlushRange(workarea,16);

	card->dsp_task.prio = 255;
	card->dsp_task.iram_maddr = (u16*)MEM_VIRTUAL_TO_PHYSICAL(_cardunlockdata);
	card->dsp_task.iram_len = 352;
	card->dsp_task.iram_addr = 0x0000;
	card->dsp_task.init_vec = 16;
	card->dsp_task.res_cb = NULL;
	card->dsp_task.req_cb = NULL;
	card->dsp_task.init_cb = __dsp_initcallback;
	card->dsp_task.done_cb = __dsp_donecallback;
	DSP_AddTask(&card->dsp_task);

	key[0] = a;
	key[1] = b;
	key[2] = c;

	return CARD_ERROR_READY;
}