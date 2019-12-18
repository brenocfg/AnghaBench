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
struct d3d8_texture_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  d3d8_video_texture_load_d3d (struct d3d8_texture_info*,uintptr_t*) ; 

__attribute__((used)) static int d3d8_video_texture_load_wrap_d3d(void *data)
{
   uintptr_t id = 0;
   struct d3d8_texture_info *info = (struct d3d8_texture_info*)data;
   if (!info)
      return 0;
   d3d8_video_texture_load_d3d(info, &id);
   return id;
}