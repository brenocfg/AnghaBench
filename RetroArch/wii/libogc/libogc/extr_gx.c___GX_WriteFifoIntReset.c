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
typedef  int u8 ;
struct TYPE_2__ {int cpCLreg; } ;

/* Variables and functions */
 int _SHIFTL (int,int,int) ; 
 TYPE_1__* __gx ; 
 int* _cpReg ; 

__attribute__((used)) static __inline__ void __GX_WriteFifoIntReset(u8 inthi,u8 intlo)
{
	__gx->cpCLreg = ((__gx->cpCLreg&~0x03)|(_SHIFTL(intlo,1,1))|(inthi&1));
	_cpReg[2] = __gx->cpCLreg;
}