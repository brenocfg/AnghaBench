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
typedef  enum display_metric_types { ____Placeholder_display_metric_types } display_metric_types ;
typedef  int /*<<< orphan*/  density ;

/* Variables and functions */
#define  DISPLAY_METRIC_DPI 131 
#define  DISPLAY_METRIC_MM_HEIGHT 130 
#define  DISPLAY_METRIC_MM_WIDTH 129 
#define  DISPLAY_METRIC_NONE 128 
 int PROP_VALUE_MAX ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  dpi_get_density (char*,int) ; 
 int /*<<< orphan*/  string_is_empty (char*) ; 

__attribute__((used)) static bool android_gfx_ctx_get_metrics(void *data,
	enum display_metric_types type, float *value)
{
   static int dpi = -1;

   switch (type)
   {
      case DISPLAY_METRIC_MM_WIDTH:
         return false;
      case DISPLAY_METRIC_MM_HEIGHT:
         return false;
      case DISPLAY_METRIC_DPI:
         if (dpi == -1)
         {
            char density[PROP_VALUE_MAX];
            density[0] = '\0';

            dpi_get_density(density, sizeof(density));
            if (string_is_empty(density))
               goto dpi_fallback;
            dpi    = atoi(density);

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
   /* add a fallback in case the device doesn't report DPI.
    * Hopefully fixes issues with the moto G2. */
   dpi    = 90;
   *value = (float)dpi;
   return true;
}