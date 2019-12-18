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
struct TYPE_3__ {int filter_palette_zero; int text_compression; scalar_t__ add_id; scalar_t__ predefined_filters; scalar_t__ force_palette; int /*<<< orphan*/  auto_convert; int /*<<< orphan*/  filter_strategy; int /*<<< orphan*/  zlibsettings; } ;
typedef  TYPE_1__ LodePNGEncoderSettings ;

/* Variables and functions */
 int /*<<< orphan*/  LAC_AUTO ; 
 int /*<<< orphan*/  LFS_MINSUM ; 
 int /*<<< orphan*/  lodepng_compress_settings_init (int /*<<< orphan*/ *) ; 

void lodepng_encoder_settings_init(LodePNGEncoderSettings* settings)
{
  lodepng_compress_settings_init(&settings->zlibsettings);
  settings->filter_palette_zero = 1;
  settings->filter_strategy = LFS_MINSUM;
  settings->auto_convert = LAC_AUTO;
  settings->force_palette = 0;
  settings->predefined_filters = 0;
#ifdef LODEPNG_COMPILE_ANCILLARY_CHUNKS
  settings->add_id = 0;
  settings->text_compression = 1;
#endif /*LODEPNG_COMPILE_ANCILLARY_CHUNKS*/
}