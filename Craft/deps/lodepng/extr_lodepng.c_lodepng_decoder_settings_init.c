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
struct TYPE_3__ {int color_convert; int read_text_chunks; int /*<<< orphan*/  zlibsettings; scalar_t__ fix_png; scalar_t__ ignore_crc; scalar_t__ remember_unknown_chunks; } ;
typedef  TYPE_1__ LodePNGDecoderSettings ;

/* Variables and functions */
 int /*<<< orphan*/  lodepng_decompress_settings_init (int /*<<< orphan*/ *) ; 

void lodepng_decoder_settings_init(LodePNGDecoderSettings* settings)
{
  settings->color_convert = 1;
#ifdef LODEPNG_COMPILE_ANCILLARY_CHUNKS
  settings->read_text_chunks = 1;
  settings->remember_unknown_chunks = 0;
#endif /*LODEPNG_COMPILE_ANCILLARY_CHUNKS*/
  settings->ignore_crc = 0;
  settings->fix_png = 0;
  lodepng_decompress_settings_init(&settings->zlibsettings);
}