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
struct TYPE_2__ {scalar_t__ left_thumbnail; scalar_t__ thumbnail; } ;
typedef  TYPE_1__ xmb_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  video_driver_texture_unload (scalar_t__*) ; 

__attribute__((used)) static void xmb_unload_thumbnail_textures(void *data)
{
   xmb_handle_t *xmb = (xmb_handle_t*)data;
   if (!xmb)
      return;

   if (xmb->thumbnail)
      video_driver_texture_unload(&xmb->thumbnail);
   if (xmb->left_thumbnail)
      video_driver_texture_unload(&xmb->left_thumbnail);
}