#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int length; scalar_t__ offset; } ;
struct TYPE_7__ {int length; scalar_t__ offset; } ;
struct TYPE_6__ {int length; } ;
struct TYPE_5__ {int length; } ;
struct fb_var_screeninfo {int bits_per_pixel; TYPE_4__ blue; TYPE_3__ red; TYPE_2__ transp; TYPE_1__ green; } ;

/* Variables and functions */
 int EINVAL ; 
 int PIX_FMT_BGR1555 ; 
 int PIX_FMT_BGR565 ; 
 int PIX_FMT_BGR888PACK ; 
 int PIX_FMT_BGR888UNPACK ; 
 int PIX_FMT_BGRA888 ; 
 int PIX_FMT_PSEUDOCOLOR ; 
 int PIX_FMT_RGB1555 ; 
 int PIX_FMT_RGB565 ; 
 int PIX_FMT_RGB888PACK ; 
 int PIX_FMT_RGB888UNPACK ; 
 int PIX_FMT_RGBA888 ; 

__attribute__((used)) static int determine_best_pix_fmt(struct fb_var_screeninfo *var)
{
	/*
	 * Pseudocolor mode?
	 */
	if (var->bits_per_pixel == 8)
		return PIX_FMT_PSEUDOCOLOR;

	/*
	 * Check for 565/1555.
	 */
	if (var->bits_per_pixel == 16 && var->red.length <= 5 &&
	    var->green.length <= 6 && var->blue.length <= 5) {
		if (var->transp.length == 0) {
			if (var->red.offset >= var->blue.offset)
				return PIX_FMT_RGB565;
			else
				return PIX_FMT_BGR565;
		}

		if (var->transp.length == 1 && var->green.length <= 5) {
			if (var->red.offset >= var->blue.offset)
				return PIX_FMT_RGB1555;
			else
				return PIX_FMT_BGR1555;
		}

		/* fall through */
	}

	/*
	 * Check for 888/A888.
	 */
	if (var->bits_per_pixel <= 32 && var->red.length <= 8 &&
	    var->green.length <= 8 && var->blue.length <= 8) {
		if (var->bits_per_pixel == 24 && var->transp.length == 0) {
			if (var->red.offset >= var->blue.offset)
				return PIX_FMT_RGB888PACK;
			else
				return PIX_FMT_BGR888PACK;
		}

		if (var->bits_per_pixel == 32 && var->transp.length == 8) {
			if (var->red.offset >= var->blue.offset)
				return PIX_FMT_RGBA888;
			else
				return PIX_FMT_BGRA888;
		} else {
			if (var->red.offset >= var->blue.offset)
				return PIX_FMT_RGB888UNPACK;
			else
				return PIX_FMT_BGR888UNPACK;
		}

		/* fall through */
	}

	return -EINVAL;
}