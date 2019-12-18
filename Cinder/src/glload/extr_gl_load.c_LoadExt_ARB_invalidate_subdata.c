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
typedef  scalar_t__ PFNGLINVALIDATETEXSUBIMAGEPROC ;
typedef  scalar_t__ PFNGLINVALIDATETEXIMAGEPROC ;
typedef  scalar_t__ PFNGLINVALIDATESUBFRAMEBUFFERPROC ;
typedef  scalar_t__ PFNGLINVALIDATEFRAMEBUFFERPROC ;
typedef  scalar_t__ PFNGLINVALIDATEBUFFERSUBDATAPROC ;
typedef  scalar_t__ PFNGLINVALIDATEBUFFERDATAPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glInvalidateBufferData ; 
 scalar_t__ _funcptr_glInvalidateBufferSubData ; 
 scalar_t__ _funcptr_glInvalidateFramebuffer ; 
 scalar_t__ _funcptr_glInvalidateSubFramebuffer ; 
 scalar_t__ _funcptr_glInvalidateTexImage ; 
 scalar_t__ _funcptr_glInvalidateTexSubImage ; 

__attribute__((used)) static int LoadExt_ARB_invalidate_subdata()
{
	int numFailed = 0;
	_funcptr_glInvalidateBufferData = (PFNGLINVALIDATEBUFFERDATAPROC)IntGetProcAddress("glInvalidateBufferData");
	if(!_funcptr_glInvalidateBufferData) ++numFailed;
	_funcptr_glInvalidateBufferSubData = (PFNGLINVALIDATEBUFFERSUBDATAPROC)IntGetProcAddress("glInvalidateBufferSubData");
	if(!_funcptr_glInvalidateBufferSubData) ++numFailed;
	_funcptr_glInvalidateFramebuffer = (PFNGLINVALIDATEFRAMEBUFFERPROC)IntGetProcAddress("glInvalidateFramebuffer");
	if(!_funcptr_glInvalidateFramebuffer) ++numFailed;
	_funcptr_glInvalidateSubFramebuffer = (PFNGLINVALIDATESUBFRAMEBUFFERPROC)IntGetProcAddress("glInvalidateSubFramebuffer");
	if(!_funcptr_glInvalidateSubFramebuffer) ++numFailed;
	_funcptr_glInvalidateTexImage = (PFNGLINVALIDATETEXIMAGEPROC)IntGetProcAddress("glInvalidateTexImage");
	if(!_funcptr_glInvalidateTexImage) ++numFailed;
	_funcptr_glInvalidateTexSubImage = (PFNGLINVALIDATETEXSUBIMAGEPROC)IntGetProcAddress("glInvalidateTexSubImage");
	if(!_funcptr_glInvalidateTexSubImage) ++numFailed;
	return numFailed;
}