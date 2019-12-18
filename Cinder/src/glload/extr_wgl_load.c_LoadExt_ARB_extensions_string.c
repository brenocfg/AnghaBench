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
typedef  scalar_t__ PFNWGLGETEXTENSIONSSTRINGARBPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_wglGetExtensionsStringARB ; 

__attribute__((used)) static int LoadExt_ARB_extensions_string()
{
	int numFailed = 0;
	_funcptr_wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)IntGetProcAddress("wglGetExtensionsStringARB");
	if(!_funcptr_wglGetExtensionsStringARB) ++numFailed;
	return numFailed;
}