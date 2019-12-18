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
typedef  int /*<<< orphan*/  qnx_ctx_data_t ;
typedef  enum display_metric_types { ____Placeholder_display_metric_types } display_metric_types ;

/* Variables and functions */
#define  DISPLAY_METRIC_DPI 131 
#define  DISPLAY_METRIC_MM_HEIGHT 130 
#define  DISPLAY_METRIC_MM_WIDTH 129 
#define  DISPLAY_METRIC_NONE 128 
 int dpi_get_density (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool gfx_ctx_qnx__get_metrics(void *data,
    enum display_metric_types type, float *value)
{
   static int dpi = -1;
   qnx_ctx_data_t *qnx = (qnx_ctx_data_t*)data;

   switch (type)
   {
      case DISPLAY_METRIC_MM_WIDTH:
         return false;
      case DISPLAY_METRIC_MM_HEIGHT:
         return false;
      case DISPLAY_METRIC_DPI:
         if (dpi == -1)
         {
            dpi = dpi_get_density(qnx);
            if (dpi <= 0)
               goto dpi_fallback;
         }
         *value = (float)dpi;
         break;
      case DISPLAY_METRIC_NONE:
      default:
         *value = 0;
         return false;
   }

   return true;

dpi_fallback:
   /* Add a fallback in case the device doesn't report DPI.
    * Calculated as an average of all BB10 device DPIs circa 2016. */
   dpi    = 345;
   *value = (float)dpi;
   return true;
}