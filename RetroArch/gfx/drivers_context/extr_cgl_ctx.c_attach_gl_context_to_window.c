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
typedef  int GLint ;
typedef  scalar_t__ Float64 ;
typedef  int CGSWindowID ;
typedef  int CGSSurfaceID ;
typedef  int CGSConnectionID ;
typedef  int /*<<< orphan*/  CGLContextObj ;
typedef  int /*<<< orphan*/  CFNumberRef ;
typedef  scalar_t__ CFDictionaryRef ;
typedef  int /*<<< orphan*/  CFArrayRef ;

/* Variables and functions */
 scalar_t__ CFArrayGetValueAtIndex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CFDictionaryGetValue (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFNumberGetValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFSTR (char*) ; 
 int /*<<< orphan*/  CGLGetParameter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ CGLSetSurface (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  CGRectMake (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ CGSAddSurface (int,int,int*) ; 
 int CGSMainConnectionID () ; 
 scalar_t__ CGSOrderSurface (int,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ CGSSetSurfaceBounds (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CGWindowListCopyWindowInfo (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kCFNumberFloat64Type ; 
 scalar_t__ kCGErrorSuccess ; 
 int /*<<< orphan*/  kCGLCPHasDrawable ; 
 int /*<<< orphan*/  kCGWindowBounds ; 
 int /*<<< orphan*/  kCGWindowListOptionIncludingWindow ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static CGSSurfaceID attach_gl_context_to_window(CGLContextObj glCtx,
   CGSWindowID wid, int *width, int *height)
{
    CFArrayRef wins;
    CFDictionaryRef win, bnd;
    GLint params = 0;
    Float64 w = 0, h = 0;
    CGSSurfaceID sid = 0;
    CGSConnectionID cid = CGSMainConnectionID();

    printf("cid:%d wid:%d\n", cid, wid);

    /* determine window size */
    /* FIXME/TODO - CGWindowListCopyWindowInfo was introduced on OSX 10.5,
     * find alternative for lower versions. */
    wins = CGWindowListCopyWindowInfo(kCGWindowListOptionIncludingWindow, wid); /* expect one result only */
    win = (CFDictionaryRef)CFArrayGetValueAtIndex(wins, 0);
    bnd = (CFDictionaryRef)CFDictionaryGetValue(win, kCGWindowBounds);
    CFNumberGetValue((CFNumberRef)CFDictionaryGetValue((CFDictionaryRef)bnd, CFSTR("Width")),
       kCFNumberFloat64Type, &w);
    CFNumberGetValue((CFNumberRef)CFDictionaryGetValue(bnd, CFSTR("Height")),
       kCFNumberFloat64Type, &h);
    CFRelease(wins);

    /* create a surface. */
    if(CGSAddSurface(cid, wid, &sid) != kCGErrorSuccess)
    {
       printf("ERR: no surface\n");
    }
    printf("sid:%d\n", sid);

    /* set surface size, and order it frontmost */
    if(CGSSetSurfaceBounds(cid, wid, sid, CGRectMake(0, 0, w, h)) != kCGErrorSuccess)
       printf("ERR: cant set bounds\n");
    if(CGSOrderSurface(cid, wid, sid, 1, 0) != kCGErrorSuccess)
       printf("ERR: cant order front\n");

    /* attach context to the surface */
    if(CGLSetSurface(glCtx, cid, wid, sid) != kCGErrorSuccess)
    {
       printf("ERR: cant set surface\n");
    }

    /* check drawable */
    CGLGetParameter(glCtx, kCGLCPHasDrawable, &params);
    if(params != 1)
    {
       printf("ERR: no drawable\n");
    }

    *width  = (int)w;
    *height = (int)h;

    return sid;
}