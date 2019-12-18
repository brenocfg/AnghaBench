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
struct TYPE_2__ {float clock; float htotal; float vtotal; } ;

/* Variables and functions */
 TYPE_1__* g_drm_mode ; 

float drm_get_refresh_rate(void *data)
{
   float refresh_rate = 0.0f;

   if (g_drm_mode)
   {
      refresh_rate = g_drm_mode->clock * 1000.0f / g_drm_mode->htotal / g_drm_mode->vtotal;
   }

   return refresh_rate;
}