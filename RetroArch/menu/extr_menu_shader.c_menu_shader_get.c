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
struct video_shader {int dummy; } ;

/* Variables and functions */
 struct video_shader* menu_driver_shader ; 
 scalar_t__ video_shader_any_supported () ; 

struct video_shader *menu_shader_get(void)
{
   if (video_shader_any_supported())
      return menu_driver_shader;
   return NULL;
}