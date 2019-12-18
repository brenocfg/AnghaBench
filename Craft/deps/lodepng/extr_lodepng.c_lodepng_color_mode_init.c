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
struct TYPE_3__ {int bitdepth; scalar_t__ palettesize; scalar_t__ palette; int /*<<< orphan*/  colortype; scalar_t__ key_b; scalar_t__ key_g; scalar_t__ key_r; scalar_t__ key_defined; } ;
typedef  TYPE_1__ LodePNGColorMode ;

/* Variables and functions */
 int /*<<< orphan*/  LCT_RGBA ; 

void lodepng_color_mode_init(LodePNGColorMode* info)
{
  info->key_defined = 0;
  info->key_r = info->key_g = info->key_b = 0;
  info->colortype = LCT_RGBA;
  info->bitdepth = 8;
  info->palette = 0;
  info->palettesize = 0;
}