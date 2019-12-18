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
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int PAD_ENABLEDMASK (size_t) ; 
 int SI_GC_STANDARD ; 
 int SI_GC_WIRELESS ; 
 int SI_TYPE_GC ; 
 int SI_TYPE_MASK ; 
 int SI_Transfer (size_t,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SI_WIRELESS_CONT_MASK ; 
 int SI_WIRELESS_FIX_ID ; 
 int SI_WIRELESS_IR ; 
 int SI_WIRELESS_LITE ; 
 int SI_WIRELESS_RECEIVED ; 
 int /*<<< orphan*/  __pad_cmdcalibrate ; 
 int /*<<< orphan*/ * __pad_cmdprobedevice ; 
 int /*<<< orphan*/  __pad_cmdreadorigin ; 
 int /*<<< orphan*/  __pad_doreset () ; 
 int /*<<< orphan*/  __pad_enable (size_t) ; 
 int /*<<< orphan*/ * __pad_origin ; 
 int /*<<< orphan*/  __pad_origincallback ; 
 int __pad_pendingbits ; 
 int /*<<< orphan*/  __pad_probecallback ; 
 int __pad_recalibratebits ; 
 size_t __pad_resettingchan ; 
 int __pad_spec ; 
 int* __pad_type ; 

__attribute__((used)) static void __pad_typeandstatuscallback(s32 chan,u32 type)
{
	u32 recal_bits,mask,ret = 0;
	mask = PAD_ENABLEDMASK(__pad_resettingchan);
	recal_bits = __pad_recalibratebits&mask;
	__pad_recalibratebits &= ~mask;

	if(type&0x0f) {
		__pad_doreset();
		return;
	}

	__pad_type[__pad_resettingchan] = (type&~0xff);
	if(((type&SI_TYPE_MASK)-SI_TYPE_GC)
		|| !(type&SI_GC_STANDARD)) {
		__pad_doreset();
		return;
	}

	if(__pad_spec<2) {
		__pad_enable(__pad_resettingchan);
		__pad_doreset();
		return;
	}

	if(!(type&SI_GC_WIRELESS) || type&SI_WIRELESS_IR) {
		if(recal_bits) ret = SI_Transfer(__pad_resettingchan,&__pad_cmdcalibrate,3,__pad_origin[__pad_resettingchan],10,__pad_origincallback,0);
		else ret = SI_Transfer(__pad_resettingchan,&__pad_cmdreadorigin,1,__pad_origin[__pad_resettingchan],10,__pad_origincallback,0);
	} else if(type&SI_WIRELESS_FIX_ID && !(type&SI_WIRELESS_CONT_MASK) && !(type&SI_WIRELESS_LITE)) {
		if(type&SI_WIRELESS_RECEIVED) ret = SI_Transfer(__pad_resettingchan,&__pad_cmdreadorigin,1,__pad_origin[__pad_resettingchan],10,__pad_origincallback,0);
		else ret = SI_Transfer(__pad_resettingchan,&__pad_cmdprobedevice[__pad_resettingchan],3,__pad_origin[__pad_resettingchan],8,__pad_probecallback,0);
	}
	if(!ret) {
		__pad_pendingbits |= mask;
		__pad_doreset();
	}
}