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
struct TYPE_2__ {int used; int /*<<< orphan*/  pixmap; scalar_t__ egl_image; } ;
typedef  int /*<<< orphan*/  KHRN_IMAGE_WRAP_T ;

/* Variables and functions */
 int NUM_PIXMAP_BINDINGS ; 
 int /*<<< orphan*/  khrn_platform_release_pixmap_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* pixmap_binding ; 
 int /*<<< orphan*/  platform_get_pixmap_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_egl_image_color_data (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int,int) ; 

__attribute__((used)) static void send_bound_pixmap(int i)
{
   KHRN_IMAGE_WRAP_T image;

   vcos_log_trace("send_bound_pixmap %d %d", i, (int)pixmap_binding[i].egl_image);

   vcos_assert(i >= 0 && i < NUM_PIXMAP_BINDINGS);
   vcos_assert(pixmap_binding[i].used);

   platform_get_pixmap_info(pixmap_binding[i].pixmap, &image);
   set_egl_image_color_data(pixmap_binding[i].egl_image, &image);
   khrn_platform_release_pixmap_info(pixmap_binding[i].pixmap, &image);
}