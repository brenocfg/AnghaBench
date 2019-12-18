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
typedef  scalar_t__ PFNGLMAPBUFFERRANGEPROC ;
typedef  scalar_t__ PFNGLFLUSHMAPPEDBUFFERRANGEPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glFlushMappedBufferRange ; 
 scalar_t__ _funcptr_glMapBufferRange ; 

__attribute__((used)) static int LoadExt_ARB_map_buffer_range()
{
	int numFailed = 0;
	_funcptr_glFlushMappedBufferRange = (PFNGLFLUSHMAPPEDBUFFERRANGEPROC)IntGetProcAddress("glFlushMappedBufferRange");
	if(!_funcptr_glFlushMappedBufferRange) ++numFailed;
	_funcptr_glMapBufferRange = (PFNGLMAPBUFFERRANGEPROC)IntGetProcAddress("glMapBufferRange");
	if(!_funcptr_glMapBufferRange) ++numFailed;
	return numFailed;
}