#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fb_var_screeninfo {int bits_per_pixel; int /*<<< orphan*/  pixclock; } ;
struct TYPE_3__ {scalar_t__ smem_len; } ;
struct fb_info {TYPE_1__ fix; int /*<<< orphan*/  device; struct cirrusfb_info* par; } ;
struct cirrusfb_info {size_t btype; int multiplexing; int doubleVCLK; } ;
struct TYPE_4__ {long* maxclock; } ;

/* Variables and functions */
#define  BT_ALPINE 131 
#define  BT_GD5480 130 
#define  BT_PICASSO4 129 
#define  BT_SD64 128 
 int EINVAL ; 
 scalar_t__ MB_ ; 
 long PICOS2KHZ (int /*<<< orphan*/ ) ; 
 TYPE_2__* cirrusfb_board_info ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,long) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,long) ; 

__attribute__((used)) static int cirrusfb_check_pixclock(const struct fb_var_screeninfo *var,
				   struct fb_info *info)
{
	long freq;
	long maxclock;
	struct cirrusfb_info *cinfo = info->par;
	unsigned maxclockidx = var->bits_per_pixel >> 3;

	/* convert from ps to kHz */
	freq = PICOS2KHZ(var->pixclock);

	dev_dbg(info->device, "desired pixclock: %ld kHz\n", freq);

	maxclock = cirrusfb_board_info[cinfo->btype].maxclock[maxclockidx];
	cinfo->multiplexing = 0;

	/* If the frequency is greater than we can support, we might be able
	 * to use multiplexing for the video mode */
	if (freq > maxclock) {
		dev_err(info->device,
			"Frequency greater than maxclock (%ld kHz)\n",
			maxclock);
		return -EINVAL;
	}
	/*
	 * Additional constraint: 8bpp uses DAC clock doubling to allow maximum
	 * pixel clock
	 */
	if (var->bits_per_pixel == 8) {
		switch (cinfo->btype) {
		case BT_ALPINE:
		case BT_SD64:
		case BT_PICASSO4:
			if (freq > 85500)
				cinfo->multiplexing = 1;
			break;
		case BT_GD5480:
			if (freq > 135100)
				cinfo->multiplexing = 1;
			break;

		default:
			break;
		}
	}

	/* If we have a 1MB 5434, we need to put ourselves in a mode where
	 * the VCLK is double the pixel clock. */
	cinfo->doubleVCLK = 0;
	if (cinfo->btype == BT_SD64 && info->fix.smem_len <= MB_ &&
	    var->bits_per_pixel == 16) {
		cinfo->doubleVCLK = 1;
	}

	return 0;
}