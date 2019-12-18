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
typedef  int /*<<< orphan*/  uint16_t ;
struct filter_data {int /*<<< orphan*/  burst_toggle; int /*<<< orphan*/  burst; int /*<<< orphan*/  ntsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  retroarch_snes_ntsc_blit (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  retroarch_snes_ntsc_blit_hires (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static void blargg_ntsc_snes_render_rgb565(void *data, int width, int height,
      int first, int last,
      uint16_t *input, int pitch, uint16_t *output, int outpitch)
{
   struct filter_data *filt = (struct filter_data*)data;
   if(width <= 256)
      retroarch_snes_ntsc_blit(filt->ntsc, input, pitch, filt->burst,
            width, height, output, outpitch * 2, first, last);
   else
      retroarch_snes_ntsc_blit_hires(filt->ntsc, input, pitch, filt->burst,
            width, height, output, outpitch * 2, first, last);

   filt->burst ^= filt->burst_toggle;
}