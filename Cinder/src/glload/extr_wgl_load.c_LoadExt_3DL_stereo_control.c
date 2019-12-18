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
typedef  scalar_t__ PFNWGLSETSTEREOEMITTERSTATE3DLPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_wglSetStereoEmitterState3DL ; 

__attribute__((used)) static int LoadExt_3DL_stereo_control()
{
	int numFailed = 0;
	_funcptr_wglSetStereoEmitterState3DL = (PFNWGLSETSTEREOEMITTERSTATE3DLPROC)IntGetProcAddress("wglSetStereoEmitterState3DL");
	if(!_funcptr_wglSetStereoEmitterState3DL) ++numFailed;
	return numFailed;
}