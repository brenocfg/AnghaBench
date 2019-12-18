#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  size_t u32 ;
struct TYPE_2__ {int chan; int in_bytes; scalar_t__ in; } ;

/* Variables and functions */
 int SICOMCSR_COMERR ; 
 size_t SISR_COLLISION ; 
 size_t SISR_NORESPONSE ; 
 int SI_ERROR_NO_RESPONSE ; 
 int SI_ERR_BUSY ; 
 int /*<<< orphan*/  __si_cleartcinterrupt () ; 
 int* _siReg ; 
 void* gettime () ; 
 int* si_type ; 
 TYPE_1__ sicntrl ; 
 void** typeTime ; 
 void** xferTime ; 

__attribute__((used)) static u32 __si_completetransfer()
{
	u32 val,cnt,i;
	u32 *in;
	u32 sisr = _siReg[14];

	__si_cleartcinterrupt();

	if(sicntrl.chan==-1) return sisr;

	xferTime[sicntrl.chan] = gettime();

	in = (u32*)sicntrl.in;
	cnt = (sicntrl.in_bytes/4);
	for(i=0;i<cnt;i++) in[i] = _siReg[32+i];
	if(sicntrl.in_bytes&0x03) {
		val = _siReg[32+cnt];
		for(i=0;i<(sicntrl.in_bytes&0x03);i++) ((u8*)in)[(cnt*4)+i] = (val>>((3-i)*8))&0xff;
	}
	if(_siReg[13]&SICOMCSR_COMERR) {
		sisr = (sisr>>((3-sicntrl.chan)*8))&0x0f;
		if(sisr&SISR_NORESPONSE && !(si_type[sicntrl.chan]&SI_ERR_BUSY)) si_type[sicntrl.chan] = SI_ERROR_NO_RESPONSE;
		if(!sisr) sisr = SISR_COLLISION;
	} else {
		typeTime[sicntrl.chan] = gettime();
		sisr = 0;
	}

	sicntrl.chan = -1;
	return sisr;
}