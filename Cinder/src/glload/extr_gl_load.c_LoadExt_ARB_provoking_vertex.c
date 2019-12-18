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
typedef  scalar_t__ PFNGLPROVOKINGVERTEXPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glProvokingVertex ; 

__attribute__((used)) static int LoadExt_ARB_provoking_vertex()
{
	int numFailed = 0;
	_funcptr_glProvokingVertex = (PFNGLPROVOKINGVERTEXPROC)IntGetProcAddress("glProvokingVertex");
	if(!_funcptr_glProvokingVertex) ++numFailed;
	return numFailed;
}