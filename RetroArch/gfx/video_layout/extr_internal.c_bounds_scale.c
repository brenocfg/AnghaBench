#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ video_layout_bounds_t ;

/* Variables and functions */

void bounds_scale(
      video_layout_bounds_t *dst,
      const video_layout_bounds_t *dim)
{
   dst->x *= dim->w;
   dst->y *= dim->h;
   dst->w *= dim->w;
   dst->h *= dim->h;
}