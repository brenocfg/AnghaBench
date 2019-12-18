#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int tcint; int tcintmsk; int outlen; int inlen; int channel; int tstart; } ;
struct TYPE_5__ {int val; TYPE_1__ csrmap; } ;
typedef  TYPE_2__ sicomcsr ;
typedef  int s32 ;
struct TYPE_6__ {int chan; int in_bytes; void* in; scalar_t__ callback; } ;
typedef  scalar_t__ SICallback ;

/* Variables and functions */
 int SISR_ERRORMASK (int) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int) ; 
 int* _siReg ; 
 TYPE_3__ sicntrl ; 

__attribute__((used)) static u32 __si_transfer(s32 chan,void *out,u32 out_len,void *in,u32 in_len,SICallback cb)
{
	u32 level,cnt,i;
	sicomcsr csr;
	_CPU_ISR_Disable(level);
	if(sicntrl.chan!=-1) {
		_CPU_ISR_Restore(level);
		return 0;
	}
	_siReg[14] &= SISR_ERRORMASK(chan);

	sicntrl.chan = chan;
	sicntrl.callback = cb;
	sicntrl.in_bytes = in_len;
	sicntrl.in = in;
	cnt = ((out_len+3)/4);
	for(i=0;i<cnt;i++)  _siReg[32+i] = ((u32*)out)[i];

	csr.val = _siReg[13];
	csr.csrmap.tcint = 1;
	csr.csrmap.tcintmsk = 0;
	if(cb) csr.csrmap.tcintmsk = 1;

	if(out_len==128) out_len = 0;
	csr.csrmap.outlen = out_len&0x7f;

	if(in_len==128) in_len = 0;
	csr.csrmap.inlen = in_len&0x7f;

	csr.csrmap.channel = chan&0x03;
	csr.csrmap.tstart = 1;
	_siReg[13] = csr.val;
	_CPU_ISR_Restore(level);

	return 1;
}