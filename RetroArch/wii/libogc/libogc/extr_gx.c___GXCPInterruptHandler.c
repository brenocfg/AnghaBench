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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int cpSRreg; int cpCRreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  __GXOverflowHandler () ; 
 int /*<<< orphan*/  __GXUnderflowHandler () ; 
 TYPE_1__* __gx ; 
 int* _cpReg ; 
 int /*<<< orphan*/  breakPtCB () ; 

__attribute__((used)) static void __GXCPInterruptHandler(u32 irq,void *ctx)
{
	__gx->cpSRreg = _cpReg[0];

	if((__gx->cpCRreg&0x08) && (__gx->cpSRreg&0x02))
		__GXUnderflowHandler();

	if((__gx->cpCRreg&0x04) && (__gx->cpSRreg&0x01))
		__GXOverflowHandler();

	if((__gx->cpCRreg&0x20) && (__gx->cpSRreg&0x10)) {
		__gx->cpCRreg &= ~0x20;
		_cpReg[1] = __gx->cpCRreg;
		if(breakPtCB)
			breakPtCB();
	}
}