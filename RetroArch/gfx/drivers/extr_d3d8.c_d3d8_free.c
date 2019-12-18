#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * dev; struct TYPE_8__* shader_path; struct TYPE_8__* menu; scalar_t__ overlays_size; struct TYPE_8__* overlays; } ;
typedef  TYPE_1__ d3d8_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  d3d8_deinitialize (TYPE_1__*) ; 
 int /*<<< orphan*/  d3d8_deinitialize_symbols () ; 
 int /*<<< orphan*/  d3d8_device_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d3d8_free_overlay (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  d3d8_free_overlays (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/ * g_pD3D8 ; 
 int /*<<< orphan*/  string_is_empty (TYPE_1__*) ; 
 int /*<<< orphan*/  win32_destroy_window () ; 
 int /*<<< orphan*/  win32_monitor_from_window () ; 

__attribute__((used)) static void d3d8_free(void *data)
{
   d3d8_video_t   *d3d = (d3d8_video_t*)data;

   if (!d3d)
      return;

#ifdef HAVE_OVERLAY
   d3d8_free_overlays(d3d);
   if (d3d->overlays)
      free(d3d->overlays);
   d3d->overlays      = NULL;
   d3d->overlays_size = 0;
#endif

   d3d8_free_overlay(d3d, d3d->menu);
   if (d3d->menu)
      free(d3d->menu);
   d3d->menu          = NULL;

   d3d8_deinitialize(d3d);

   if (!string_is_empty(d3d->shader_path))
      free(d3d->shader_path);

   d3d->shader_path = NULL;
   d3d8_device_free(d3d->dev, g_pD3D8);
   d3d->dev         = NULL;
   g_pD3D8          = NULL;

   d3d8_deinitialize_symbols();

#ifndef _XBOX
   win32_monitor_from_window();
   win32_destroy_window();
#endif
   free(d3d);
}