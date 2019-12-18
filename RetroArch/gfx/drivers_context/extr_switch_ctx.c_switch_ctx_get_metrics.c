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

/* Variables and functions */
#define  DISPLAY_METRIC_DPI 128 

bool switch_ctx_get_metrics(void *data,
   enum display_metric_types type, float *value)
{
   switch (type)
   {
      case DISPLAY_METRIC_DPI:
         *value = 236.87; /* FIXME: Don't hardcode this value */
         return true;
      default:
         break;
   }

   return false;
}