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
typedef  int /*<<< orphan*/  CGLPixelFormatObj ;
typedef  int /*<<< orphan*/  CGLPixelFormatAttribute ;
typedef  int /*<<< orphan*/ * CGLContextObj ;

/* Variables and functions */
 int /*<<< orphan*/  CGLChoosePixelFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  CGLCreateContext (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  CGLDestroyPixelFormat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CGLSetParameter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  kCGLCPSwapInterval ; 
 int /*<<< orphan*/  kCGLPFAAccelerated ; 
 int /*<<< orphan*/  kCGLPFADoubleBuffer ; 

__attribute__((used)) static CGLContextObj gfx_ctx_cgl_init_create(void)
{
   GLint num, params = 1;
   CGLPixelFormatObj pix;
   CGLContextObj glCtx = NULL;
   CGLPixelFormatAttribute attributes[] = {
      kCGLPFAAccelerated,
      kCGLPFADoubleBuffer,
      (CGLPixelFormatAttribute)0
   };

   CGLChoosePixelFormat(attributes, &pix, &num);
   CGLCreateContext(pix, NULL, &glCtx);
   CGLDestroyPixelFormat(pix);

   CGLSetParameter(glCtx, kCGLCPSwapInterval, &params);

   return glCtx;
}