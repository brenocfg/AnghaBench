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
typedef  int /*<<< orphan*/  gfx_ctx_proc_t ;
typedef  int /*<<< orphan*/  CFURLRef ;
typedef  int /*<<< orphan*/  CFStringRef ;
typedef  int /*<<< orphan*/  CFBundleRef ;

/* Variables and functions */
 int /*<<< orphan*/  CFBundleCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFBundleGetFunctionPointerForName (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFSTR (char*) ; 
 int /*<<< orphan*/  CFStringCreateWithCString (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFURLCreateWithFileSystemPath (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kCFAllocatorDefault ; 
 int /*<<< orphan*/  kCFStringEncodingASCII ; 
 int /*<<< orphan*/  kCFURLPOSIXPathStyle ; 

__attribute__((used)) static gfx_ctx_proc_t gfx_ctx_cgl_get_proc_address(const char *symbol_name)
{
   CFURLRef bundle_url = CFURLCreateWithFileSystemPath(kCFAllocatorDefault,
         CFSTR
         ("/System/Library/Frameworks/OpenGL.framework"),
         kCFURLPOSIXPathStyle, true);
   CFBundleRef opengl_bundle_ref  = CFBundleCreate(kCFAllocatorDefault, bundle_url);
   CFStringRef function =  CFStringCreateWithCString(kCFAllocatorDefault, symbol_name,
         kCFStringEncodingASCII);
   gfx_ctx_proc_t ret = (gfx_ctx_proc_t)CFBundleGetFunctionPointerForName(
         opengl_bundle_ref, function);

   CFRelease(bundle_url);
   CFRelease(function);
   CFRelease(opengl_bundle_ref);

   return ret;
}