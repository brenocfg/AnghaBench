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
typedef  int u32 ;
struct sram_channel {int /*<<< orphan*/  vid_cdt_size; int /*<<< orphan*/  vid_active_ctl2; int /*<<< orphan*/  vid_active_ctl1; int /*<<< orphan*/  vid_fmt_ctl; } ;
struct cx25821_dev {int _lines_count_ch2; scalar_t__ _isNTSC_ch2; } ;

/* Variables and functions */
 int PIXEL_ENGINE_VIP1 ; 
 int VID_CDT_SIZE ; 
 int WIDTH_D1 ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cx25821_set_pixelengine_ch2(struct cx25821_dev *dev,
					struct sram_channel *ch, int pix_format)
{
	int width = WIDTH_D1;
	int height = dev->_lines_count_ch2;
	int num_lines, odd_num_lines;
	u32 value;
	int vip_mode = PIXEL_ENGINE_VIP1;

	value = ((pix_format & 0x3) << 12) | (vip_mode & 0x7);
	value &= 0xFFFFFFEF;
	value |= dev->_isNTSC_ch2 ? 0 : 0x10;
	cx_write(ch->vid_fmt_ctl, value);

	// set number of active pixels in each line. Default is 720 pixels in both NTSC and PAL format
	cx_write(ch->vid_active_ctl1, width);

	num_lines = (height / 2) & 0x3FF;
	odd_num_lines = num_lines;

	if (dev->_isNTSC_ch2) {
		odd_num_lines += 1;
	}

	value = (num_lines << 16) | odd_num_lines;

	// set number of active lines in field 0 (top) and field 1 (bottom)
	cx_write(ch->vid_active_ctl2, value);

	cx_write(ch->vid_cdt_size, VID_CDT_SIZE >> 3);
}