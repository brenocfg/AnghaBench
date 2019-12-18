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
typedef  int uint8_t ;
typedef  int GRAPHICS_RESOURCE_TYPE_T ;
typedef  int EGLint ;

/* Variables and functions */
#define  EGL_ALPHA_SIZE 134 
#define  EGL_BLUE_SIZE 133 
#define  EGL_GREEN_SIZE 132 
#define  EGL_RED_SIZE 131 
#define  GRAPHICS_RESOURCE_RGB565 130 
#define  GRAPHICS_RESOURCE_RGB888 129 
#define  GRAPHICS_RESOURCE_RGBA32 128 
 int countof (int*) ; 
 int /*<<< orphan*/  vcos_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gx_egl_attrib_colours(EGLint *attribs, GRAPHICS_RESOURCE_TYPE_T res_type)
{
   int i, n;
   static EGLint rgba[] = {EGL_RED_SIZE, EGL_GREEN_SIZE, EGL_BLUE_SIZE, EGL_ALPHA_SIZE};
   static uint8_t rgb565[] = {5,6,5,0};
   static uint8_t rgb888[] = {8,8,8,0};
   static uint8_t rgb32a[] = {8,8,8,8};

   uint8_t *sizes = NULL;

   switch (res_type)
   {
      case GRAPHICS_RESOURCE_RGB565:
         sizes = rgb565;
         break;
      case GRAPHICS_RESOURCE_RGB888:
         sizes = rgb888;
         break;
      case GRAPHICS_RESOURCE_RGBA32:
         sizes = rgb32a;
         break;
      default:
         vcos_assert(0);
         return -1;
   }
   for (n=0, i=0; i<countof(rgba); i++)
   {
      attribs[n++] = rgba[i];
      attribs[n++] = sizes[i];
   }
   return n;
}