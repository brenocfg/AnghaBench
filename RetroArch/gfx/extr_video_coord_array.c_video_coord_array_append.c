#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  lut_tex_coord; int /*<<< orphan*/  tex_coord; int /*<<< orphan*/  color; int /*<<< orphan*/  vertex; int /*<<< orphan*/  vertices; } ;
typedef  TYPE_2__ video_coords_t ;
struct TYPE_7__ {unsigned int vertices; scalar_t__ lut_tex_coord; scalar_t__ tex_coord; scalar_t__ color; scalar_t__ vertex; } ;
struct TYPE_9__ {unsigned int allocated; TYPE_1__ coords; } ;
typedef  TYPE_3__ video_coord_array_t ;

/* Variables and functions */
 unsigned int MIN (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,size_t) ; 
 unsigned int next_pow2 (unsigned int) ; 
 int /*<<< orphan*/  video_coord_array_resize (TYPE_3__*,unsigned int) ; 

bool video_coord_array_append(video_coord_array_t *ca,
      const video_coords_t *coords, unsigned count)
{
   size_t base_size, offset;
   count          = MIN(count, coords->vertices);

   if (ca->coords.vertices + count >= ca->allocated)
   {
      unsigned cap = next_pow2(ca->coords.vertices + count);
      if (!video_coord_array_resize(ca, cap))
         return false;
   }

   base_size = count * sizeof(float);
   offset    = ca->coords.vertices;

   /* XXX: I wish we used interlaced arrays so
    * we could call memcpy only once. */
   memcpy(ca->coords.vertex        + offset * 2,
         coords->vertex, base_size * 2);

   memcpy(ca->coords.color         + offset * 4,
         coords->color, base_size * 4);

   memcpy(ca->coords.tex_coord     + offset * 2,
         coords->tex_coord, base_size * 2);

   memcpy(ca->coords.lut_tex_coord + offset * 2,
         coords->lut_tex_coord, base_size * 2);

   ca->coords.vertices += count;

   return true;
}