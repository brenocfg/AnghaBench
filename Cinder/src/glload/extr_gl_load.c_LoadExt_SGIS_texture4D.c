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
typedef  scalar_t__ PFNGLTEXSUBIMAGE4DSGISPROC ;
typedef  scalar_t__ PFNGLTEXIMAGE4DSGISPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glTexImage4DSGIS ; 
 scalar_t__ _funcptr_glTexSubImage4DSGIS ; 

__attribute__((used)) static int LoadExt_SGIS_texture4D()
{
	int numFailed = 0;
	_funcptr_glTexImage4DSGIS = (PFNGLTEXIMAGE4DSGISPROC)IntGetProcAddress("glTexImage4DSGIS");
	if(!_funcptr_glTexImage4DSGIS) ++numFailed;
	_funcptr_glTexSubImage4DSGIS = (PFNGLTEXSUBIMAGE4DSGISPROC)IntGetProcAddress("glTexSubImage4DSGIS");
	if(!_funcptr_glTexSubImage4DSGIS) ++numFailed;
	return numFailed;
}