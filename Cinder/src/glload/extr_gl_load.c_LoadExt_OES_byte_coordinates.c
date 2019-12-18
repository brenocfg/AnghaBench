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
typedef  scalar_t__ PFNGLVERTEX4BVOESPROC ;
typedef  scalar_t__ PFNGLVERTEX4BOESPROC ;
typedef  scalar_t__ PFNGLVERTEX3BVOESPROC ;
typedef  scalar_t__ PFNGLVERTEX3BOESPROC ;
typedef  scalar_t__ PFNGLVERTEX2BVOESPROC ;
typedef  scalar_t__ PFNGLVERTEX2BOESPROC ;
typedef  scalar_t__ PFNGLTEXCOORD4BVOESPROC ;
typedef  scalar_t__ PFNGLTEXCOORD4BOESPROC ;
typedef  scalar_t__ PFNGLTEXCOORD3BVOESPROC ;
typedef  scalar_t__ PFNGLTEXCOORD3BOESPROC ;
typedef  scalar_t__ PFNGLTEXCOORD2BVOESPROC ;
typedef  scalar_t__ PFNGLTEXCOORD2BOESPROC ;
typedef  scalar_t__ PFNGLTEXCOORD1BVOESPROC ;
typedef  scalar_t__ PFNGLTEXCOORD1BOESPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD4BVOESPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD4BOESPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3BVOESPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3BOESPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2BVOESPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2BOESPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1BVOESPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1BOESPROC ;

/* Variables and functions */
 scalar_t__ IntGetProcAddress (char*) ; 
 scalar_t__ _funcptr_glMultiTexCoord1bOES ; 
 scalar_t__ _funcptr_glMultiTexCoord1bvOES ; 
 scalar_t__ _funcptr_glMultiTexCoord2bOES ; 
 scalar_t__ _funcptr_glMultiTexCoord2bvOES ; 
 scalar_t__ _funcptr_glMultiTexCoord3bOES ; 
 scalar_t__ _funcptr_glMultiTexCoord3bvOES ; 
 scalar_t__ _funcptr_glMultiTexCoord4bOES ; 
 scalar_t__ _funcptr_glMultiTexCoord4bvOES ; 
 scalar_t__ _funcptr_glTexCoord1bOES ; 
 scalar_t__ _funcptr_glTexCoord1bvOES ; 
 scalar_t__ _funcptr_glTexCoord2bOES ; 
 scalar_t__ _funcptr_glTexCoord2bvOES ; 
 scalar_t__ _funcptr_glTexCoord3bOES ; 
 scalar_t__ _funcptr_glTexCoord3bvOES ; 
 scalar_t__ _funcptr_glTexCoord4bOES ; 
 scalar_t__ _funcptr_glTexCoord4bvOES ; 
 scalar_t__ _funcptr_glVertex2bOES ; 
 scalar_t__ _funcptr_glVertex2bvOES ; 
 scalar_t__ _funcptr_glVertex3bOES ; 
 scalar_t__ _funcptr_glVertex3bvOES ; 
 scalar_t__ _funcptr_glVertex4bOES ; 
 scalar_t__ _funcptr_glVertex4bvOES ; 

__attribute__((used)) static int LoadExt_OES_byte_coordinates()
{
	int numFailed = 0;
	_funcptr_glMultiTexCoord1bOES = (PFNGLMULTITEXCOORD1BOESPROC)IntGetProcAddress("glMultiTexCoord1bOES");
	if(!_funcptr_glMultiTexCoord1bOES) ++numFailed;
	_funcptr_glMultiTexCoord1bvOES = (PFNGLMULTITEXCOORD1BVOESPROC)IntGetProcAddress("glMultiTexCoord1bvOES");
	if(!_funcptr_glMultiTexCoord1bvOES) ++numFailed;
	_funcptr_glMultiTexCoord2bOES = (PFNGLMULTITEXCOORD2BOESPROC)IntGetProcAddress("glMultiTexCoord2bOES");
	if(!_funcptr_glMultiTexCoord2bOES) ++numFailed;
	_funcptr_glMultiTexCoord2bvOES = (PFNGLMULTITEXCOORD2BVOESPROC)IntGetProcAddress("glMultiTexCoord2bvOES");
	if(!_funcptr_glMultiTexCoord2bvOES) ++numFailed;
	_funcptr_glMultiTexCoord3bOES = (PFNGLMULTITEXCOORD3BOESPROC)IntGetProcAddress("glMultiTexCoord3bOES");
	if(!_funcptr_glMultiTexCoord3bOES) ++numFailed;
	_funcptr_glMultiTexCoord3bvOES = (PFNGLMULTITEXCOORD3BVOESPROC)IntGetProcAddress("glMultiTexCoord3bvOES");
	if(!_funcptr_glMultiTexCoord3bvOES) ++numFailed;
	_funcptr_glMultiTexCoord4bOES = (PFNGLMULTITEXCOORD4BOESPROC)IntGetProcAddress("glMultiTexCoord4bOES");
	if(!_funcptr_glMultiTexCoord4bOES) ++numFailed;
	_funcptr_glMultiTexCoord4bvOES = (PFNGLMULTITEXCOORD4BVOESPROC)IntGetProcAddress("glMultiTexCoord4bvOES");
	if(!_funcptr_glMultiTexCoord4bvOES) ++numFailed;
	_funcptr_glTexCoord1bOES = (PFNGLTEXCOORD1BOESPROC)IntGetProcAddress("glTexCoord1bOES");
	if(!_funcptr_glTexCoord1bOES) ++numFailed;
	_funcptr_glTexCoord1bvOES = (PFNGLTEXCOORD1BVOESPROC)IntGetProcAddress("glTexCoord1bvOES");
	if(!_funcptr_glTexCoord1bvOES) ++numFailed;
	_funcptr_glTexCoord2bOES = (PFNGLTEXCOORD2BOESPROC)IntGetProcAddress("glTexCoord2bOES");
	if(!_funcptr_glTexCoord2bOES) ++numFailed;
	_funcptr_glTexCoord2bvOES = (PFNGLTEXCOORD2BVOESPROC)IntGetProcAddress("glTexCoord2bvOES");
	if(!_funcptr_glTexCoord2bvOES) ++numFailed;
	_funcptr_glTexCoord3bOES = (PFNGLTEXCOORD3BOESPROC)IntGetProcAddress("glTexCoord3bOES");
	if(!_funcptr_glTexCoord3bOES) ++numFailed;
	_funcptr_glTexCoord3bvOES = (PFNGLTEXCOORD3BVOESPROC)IntGetProcAddress("glTexCoord3bvOES");
	if(!_funcptr_glTexCoord3bvOES) ++numFailed;
	_funcptr_glTexCoord4bOES = (PFNGLTEXCOORD4BOESPROC)IntGetProcAddress("glTexCoord4bOES");
	if(!_funcptr_glTexCoord4bOES) ++numFailed;
	_funcptr_glTexCoord4bvOES = (PFNGLTEXCOORD4BVOESPROC)IntGetProcAddress("glTexCoord4bvOES");
	if(!_funcptr_glTexCoord4bvOES) ++numFailed;
	_funcptr_glVertex2bOES = (PFNGLVERTEX2BOESPROC)IntGetProcAddress("glVertex2bOES");
	if(!_funcptr_glVertex2bOES) ++numFailed;
	_funcptr_glVertex2bvOES = (PFNGLVERTEX2BVOESPROC)IntGetProcAddress("glVertex2bvOES");
	if(!_funcptr_glVertex2bvOES) ++numFailed;
	_funcptr_glVertex3bOES = (PFNGLVERTEX3BOESPROC)IntGetProcAddress("glVertex3bOES");
	if(!_funcptr_glVertex3bOES) ++numFailed;
	_funcptr_glVertex3bvOES = (PFNGLVERTEX3BVOESPROC)IntGetProcAddress("glVertex3bvOES");
	if(!_funcptr_glVertex3bvOES) ++numFailed;
	_funcptr_glVertex4bOES = (PFNGLVERTEX4BOESPROC)IntGetProcAddress("glVertex4bOES");
	if(!_funcptr_glVertex4bOES) ++numFailed;
	_funcptr_glVertex4bvOES = (PFNGLVERTEX4BVOESPROC)IntGetProcAddress("glVertex4bvOES");
	if(!_funcptr_glVertex4bvOES) ++numFailed;
	return numFailed;
}