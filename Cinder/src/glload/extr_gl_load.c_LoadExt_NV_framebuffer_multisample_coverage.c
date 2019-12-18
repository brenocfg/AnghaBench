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
typedef  scalar_t__ PFNGLRENDERBUFFERSTORAGEMULTISAMPLECOVERAGENVPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glRenderbufferStorageMultisampleCoverageNV ; 

__attribute__((used)) static int LoadExt_NV_framebuffer_multisample_coverage()
{
	int numFailed = 0;
	_funcptr_glRenderbufferStorageMultisampleCoverageNV = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLECOVERAGENVPROC)IntGetProcAddress("glRenderbufferStorageMultisampleCoverageNV");
	if(!_funcptr_glRenderbufferStorageMultisampleCoverageNV) ++numFailed;
	return numFailed;
}