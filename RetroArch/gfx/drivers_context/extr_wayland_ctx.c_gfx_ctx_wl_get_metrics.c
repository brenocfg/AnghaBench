#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* current_output; } ;
typedef  TYPE_2__ gfx_ctx_wayland_data_t ;
typedef  enum display_metric_types { ____Placeholder_display_metric_types } display_metric_types ;
struct TYPE_3__ {scalar_t__ physical_width; scalar_t__ physical_height; scalar_t__ width; } ;

/* Variables and functions */
#define  DISPLAY_METRIC_DPI 130 
#define  DISPLAY_METRIC_MM_HEIGHT 129 
#define  DISPLAY_METRIC_MM_WIDTH 128 

__attribute__((used)) static bool gfx_ctx_wl_get_metrics(void *data,
      enum display_metric_types type, float *value)
{
   gfx_ctx_wayland_data_t *wl = (gfx_ctx_wayland_data_t*)data;

   if (!wl || !wl->current_output || wl->current_output->physical_width == 0 || wl->current_output->physical_height == 0)
      return false;

   switch (type)
   {
      case DISPLAY_METRIC_MM_WIDTH:
         *value = (float)wl->current_output->physical_width;
         break;

      case DISPLAY_METRIC_MM_HEIGHT:
         *value = (float)wl->current_output->physical_height;
         break;

      case DISPLAY_METRIC_DPI:
         *value = (float)wl->current_output->width * 25.4f / (float)wl->current_output->physical_width;
         break;

      default:
         *value = 0.0f;
         return false;
   }

   return true;
}