#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ phys_defined; scalar_t__ time_defined; scalar_t__ background_b; scalar_t__ background_g; scalar_t__ background_r; scalar_t__ background_defined; scalar_t__ filter_method; scalar_t__ compression_method; scalar_t__ interlace_method; int /*<<< orphan*/  color; } ;
typedef  TYPE_1__ LodePNGInfo ;

/* Variables and functions */
 int /*<<< orphan*/  LodePNGIText_init (TYPE_1__*) ; 
 int /*<<< orphan*/  LodePNGText_init (TYPE_1__*) ; 
 int /*<<< orphan*/  LodePNGUnknownChunks_init (TYPE_1__*) ; 
 int /*<<< orphan*/  lodepng_color_mode_init (int /*<<< orphan*/ *) ; 

void lodepng_info_init(LodePNGInfo* info)
{
  lodepng_color_mode_init(&info->color);
  info->interlace_method = 0;
  info->compression_method = 0;
  info->filter_method = 0;
#ifdef LODEPNG_COMPILE_ANCILLARY_CHUNKS
  info->background_defined = 0;
  info->background_r = info->background_g = info->background_b = 0;

  LodePNGText_init(info);
  LodePNGIText_init(info);

  info->time_defined = 0;
  info->phys_defined = 0;

  LodePNGUnknownChunks_init(info);
#endif /*LODEPNG_COMPILE_ANCILLARY_CHUNKS*/
}