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

/* Variables and functions */
 int /*<<< orphan*/  GX_DISABLE ; 
 int /*<<< orphan*/  GX_ENABLE ; 
 int /*<<< orphan*/  GX_FALSE ; 
 int /*<<< orphan*/  GX_TRUE ; 
 int /*<<< orphan*/  LWP_SuspendThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __GX_WriteFifoIntEnable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __GX_WriteFifoIntReset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _gxcurrentlwp ; 
 int /*<<< orphan*/  _gxoverflowcount ; 
 int _gxoverflowsuspend ; 

__attribute__((used)) static void __GXOverflowHandler()
{
	if(!_gxoverflowsuspend) {
		_gxoverflowsuspend = 1;
		_gxoverflowcount++;
		__GX_WriteFifoIntEnable(GX_DISABLE,GX_ENABLE);
		__GX_WriteFifoIntReset(GX_TRUE,GX_FALSE);
		LWP_SuspendThread(_gxcurrentlwp);
	}
}