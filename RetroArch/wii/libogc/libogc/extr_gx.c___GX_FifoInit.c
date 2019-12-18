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
typedef  int /*<<< orphan*/  GXFifoObj ;

/* Variables and functions */
 int /*<<< orphan*/  IRQMASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_PI_CP ; 
 int /*<<< orphan*/  IRQ_Request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LWP_GetSelf () ; 
 int /*<<< orphan*/  __GXCPInterruptHandler ; 
 int /*<<< orphan*/  __UnmaskIrq (int /*<<< orphan*/ ) ; 
 scalar_t__ _cpgplinked ; 
 int /*<<< orphan*/  _cpufifo ; 
 int /*<<< orphan*/  _gpfifo ; 
 scalar_t__ _gxcpufifoready ; 
 int /*<<< orphan*/  _gxcurrentlwp ; 
 scalar_t__ _gxgpfifoready ; 
 scalar_t__ _gxoverflowsuspend ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void __GX_FifoInit()
{
	IRQ_Request(IRQ_PI_CP,__GXCPInterruptHandler,NULL);
	__UnmaskIrq(IRQMASK(IRQ_PI_CP));

	memset(&_cpufifo,0,sizeof(GXFifoObj));
	memset(&_gpfifo,0,sizeof(GXFifoObj));

	_gxcpufifoready = 0;
	_gxgpfifoready = 0;
	_cpgplinked = 0;
	_gxoverflowsuspend = 0;
	_gxcurrentlwp = LWP_GetSelf();
}