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
typedef  scalar_t__ PFNGLFLUSHMAPPEDBUFFERRANGEAPPLEPROC ;
typedef  scalar_t__ PFNGLBUFFERPARAMETERIAPPLEPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glBufferParameteriAPPLE ; 
 scalar_t__ _funcptr_glFlushMappedBufferRangeAPPLE ; 

__attribute__((used)) static int LoadExt_APPLE_flush_buffer_range()
{
	int numFailed = 0;
	_funcptr_glBufferParameteriAPPLE = (PFNGLBUFFERPARAMETERIAPPLEPROC)IntGetProcAddress("glBufferParameteriAPPLE");
	if(!_funcptr_glBufferParameteriAPPLE) ++numFailed;
	_funcptr_glFlushMappedBufferRangeAPPLE = (PFNGLFLUSHMAPPEDBUFFERRANGEAPPLEPROC)IntGetProcAddress("glFlushMappedBufferRangeAPPLE");
	if(!_funcptr_glFlushMappedBufferRangeAPPLE) ++numFailed;
	return numFailed;
}