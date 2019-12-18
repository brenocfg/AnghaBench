#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  display; TYPE_2__* slots; } ;
typedef  TYPE_1__ VIDTEX_T ;
struct TYPE_6__ {int /*<<< orphan*/ * image; int /*<<< orphan*/ * video_frame; } ;
typedef  TYPE_2__ VIDTEX_IMAGE_SLOT_T ;

/* Variables and functions */
 int /*<<< orphan*/  eglDestroyImageKHR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int vcos_countof (TYPE_2__*) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vidtex_destroy_images(VIDTEX_T *vt)
{
   VIDTEX_IMAGE_SLOT_T *slot;

   for (slot = vt->slots; slot < vt->slots + vcos_countof(vt->slots); slot++)
   {
      slot->video_frame = NULL;

      if (slot->image)
      {
         vcos_log_trace("Destroying EGL image %p", slot->image);
         eglDestroyImageKHR(vt->display, slot->image);
         slot->image = NULL;
      }
   }
}