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
struct TYPE_2__ {int used; int send; int /*<<< orphan*/  egl_image; int /*<<< orphan*/  pixmap; } ;
typedef  int /*<<< orphan*/  EGLNativePixmapType ;
typedef  int /*<<< orphan*/  EGLImageKHR ;

/* Variables and functions */
 int NUM_PIXMAP_BINDINGS ; 
 TYPE_1__* pixmap_binding ; 
 int /*<<< orphan*/  send_bound_pixmap (int) ; 
 int /*<<< orphan*/  vcos_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int) ; 

void khrn_platform_bind_pixmap_to_egl_image(EGLNativePixmapType pixmap, EGLImageKHR egl_image, bool send)
{
   int i;
   for (i = 0; i < NUM_PIXMAP_BINDINGS; i++)
   {
      if (!pixmap_binding[i].used)
      {

         vcos_log_trace("khrn_platform_bind_pixmap_to_egl_image %d", i);

         pixmap_binding[i].used = true;
         pixmap_binding[i].pixmap = pixmap;
         pixmap_binding[i].egl_image = egl_image;
         pixmap_binding[i].send = send;
         if(send)
            send_bound_pixmap(i);
         return;
      }
   }
   vcos_assert(0);  /* Not enough NUM_PIXMAP_BINDINGS? */
}