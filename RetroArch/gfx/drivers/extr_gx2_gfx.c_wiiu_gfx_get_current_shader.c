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
struct TYPE_2__ {struct video_shader* shader_preset; } ;
typedef  TYPE_1__ wiiu_video_t ;
struct video_shader {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct video_shader *wiiu_gfx_get_current_shader(void *data)
{
   wiiu_video_t *wiiu = (wiiu_video_t *)data;

   if (!wiiu)
      return NULL;

   return wiiu->shader_preset;
}