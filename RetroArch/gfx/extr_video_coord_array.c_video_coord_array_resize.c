#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lut_tex_coord; int /*<<< orphan*/  tex_coord; int /*<<< orphan*/  color; int /*<<< orphan*/  vertex; } ;
struct TYPE_5__ {unsigned int allocated; TYPE_1__ coords; } ;
typedef  TYPE_2__ video_coord_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  realloc_checked (void**,int) ; 

__attribute__((used)) static bool video_coord_array_resize(video_coord_array_t *ca,
   unsigned cap)
{
   size_t base_size    = sizeof(float) * cap;

   if (!realloc_checked((void**)&ca->coords.vertex,
            2 * base_size))
      return false;
   if (!realloc_checked((void**)&ca->coords.color,
            4 * base_size))
      return false;
   if (!realloc_checked((void**)&ca->coords.tex_coord,
            2 * base_size))
      return false;
   if (!realloc_checked((void**)&ca->coords.lut_tex_coord,
            2 * base_size))
      return false;

   ca->allocated = cap;

   return true;
}