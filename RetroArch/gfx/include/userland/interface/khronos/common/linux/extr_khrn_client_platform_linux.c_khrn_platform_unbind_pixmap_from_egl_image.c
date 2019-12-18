#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int used; scalar_t__ egl_image; } ;
typedef  scalar_t__ EGLImageKHR ;

/* Variables and functions */
 int NUM_PIXMAP_BINDINGS ; 
 TYPE_1__* pixmap_binding ; 

void khrn_platform_unbind_pixmap_from_egl_image(EGLImageKHR egl_image)
{
   int i;
   for (i = 0; i < NUM_PIXMAP_BINDINGS; i++)
   {
      if (pixmap_binding[i].used && pixmap_binding[i].egl_image == egl_image)
      {
         pixmap_binding[i].used = false;
      }
   }
}