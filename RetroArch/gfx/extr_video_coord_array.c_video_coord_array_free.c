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
struct TYPE_4__ {scalar_t__ vertices; int /*<<< orphan*/ * lut_tex_coord; int /*<<< orphan*/ * tex_coord; int /*<<< orphan*/ * color; int /*<<< orphan*/ * vertex; } ;
struct TYPE_5__ {scalar_t__ allocated; TYPE_1__ coords; } ;
typedef  TYPE_2__ video_coord_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void video_coord_array_free(video_coord_array_t *ca)
{
   if (!ca->allocated)
      return;

   if (ca->coords.vertex)
      free(ca->coords.vertex);
   ca->coords.vertex        = NULL;

   if (ca->coords.color)
      free(ca->coords.color);
   ca->coords.color         = NULL;

   if (ca->coords.tex_coord)
      free(ca->coords.tex_coord);
   ca->coords.tex_coord     = NULL;

   if (ca->coords.lut_tex_coord)
      free(ca->coords.lut_tex_coord);
   ca->coords.lut_tex_coord = NULL;

   ca->coords.vertices      = 0;
   ca->allocated            = 0;
}