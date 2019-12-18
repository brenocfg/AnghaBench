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
 int /*<<< orphan*/  GX_TRUE ; 
 int /*<<< orphan*/  LWP_ResumeThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __GX_WriteFifoIntEnable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __GX_WriteFifoIntReset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _gxcurrentlwp ; 
 scalar_t__ _gxoverflowsuspend ; 

__attribute__((used)) static void __GXUnderflowHandler()
{
	if(_gxoverflowsuspend) {
		_gxoverflowsuspend = 0;
		LWP_ResumeThread(_gxcurrentlwp);
		__GX_WriteFifoIntReset(GX_TRUE,GX_TRUE);
		__GX_WriteFifoIntEnable(GX_ENABLE,GX_DISABLE);
	}
}