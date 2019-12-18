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
struct wl_output {int dummy; } ;
struct TYPE_2__ {int physical_width; int physical_height; } ;
typedef  TYPE_1__ output_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*,int,int) ; 

__attribute__((used)) static void display_handle_geometry(void *data,
      struct wl_output *output,
      int x, int y,
      int physical_width, int physical_height,
      int subpixel,
      const char *make,
      const char *model,
      int transform)
{
   (void)data;
   (void)output;
   (void)x;
   (void)y;
   (void)subpixel;
   (void)make;
   (void)model;
   (void)transform;

   output_info_t *oi          = (output_info_t*)data;
   oi->physical_width         = physical_width;
   oi->physical_height        = physical_height;

   RARCH_LOG("[Wayland]: Physical width: %d mm x %d mm.\n",
         physical_width, physical_height);
}