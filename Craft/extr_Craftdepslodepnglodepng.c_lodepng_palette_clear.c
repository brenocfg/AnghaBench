#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ palettesize; scalar_t__ palette; } ;
typedef  TYPE_1__ LodePNGColorMode ;

/* Variables and functions */
 int /*<<< orphan*/  lodepng_free (scalar_t__) ; 

void lodepng_palette_clear(LodePNGColorMode* info)
{
  if(info->palette) lodepng_free(info->palette);
  info->palette = 0;
  info->palettesize = 0;
}