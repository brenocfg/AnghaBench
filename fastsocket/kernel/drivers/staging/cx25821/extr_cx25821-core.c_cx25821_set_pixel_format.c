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
typedef  int /*<<< orphan*/  u32 ;
struct sram_channel {int /*<<< orphan*/  pix_frmt; } ;
struct cx25821_dev {int /*<<< orphan*/ * pixel_formats; } ;

/* Variables and functions */
 struct sram_channel* cx25821_sram_channels ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cx25821_set_pixel_format(struct cx25821_dev *dev, int channel_select,
			      u32 format)
{
	struct sram_channel *ch;

	if (channel_select <= 7 && channel_select >= 0) {
		ch = &cx25821_sram_channels[channel_select];
		cx_write(ch->pix_frmt, format);
		dev->pixel_formats[channel_select] = format;
	}
}