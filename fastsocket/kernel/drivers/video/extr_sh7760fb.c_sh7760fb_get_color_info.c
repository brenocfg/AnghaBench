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
typedef  int u16 ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  LDDFR_16BPP_RGB555 135 
#define  LDDFR_16BPP_RGB565 134 
#define  LDDFR_1BPP_MONO 133 
#define  LDDFR_2BPP_MONO 132 
#define  LDDFR_4BPP 131 
#define  LDDFR_4BPP_MONO 130 
#define  LDDFR_6BPP_MONO 129 
#define  LDDFR_8BPP 128 
 int LDDFR_COLOR_MASK ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 

__attribute__((used)) static int sh7760fb_get_color_info(struct device *dev,
				   u16 lddfr, int *bpp, int *gray)
{
	int lbpp, lgray;

	lgray = lbpp = 0;

	switch (lddfr & LDDFR_COLOR_MASK) {
	case LDDFR_1BPP_MONO:
		lgray = 1;
		lbpp = 1;
		break;
	case LDDFR_2BPP_MONO:
		lgray = 1;
		lbpp = 2;
		break;
	case LDDFR_4BPP_MONO:
		lgray = 1;
	case LDDFR_4BPP:
		lbpp = 4;
		break;
	case LDDFR_6BPP_MONO:
		lgray = 1;
	case LDDFR_8BPP:
		lbpp = 8;
		break;
	case LDDFR_16BPP_RGB555:
	case LDDFR_16BPP_RGB565:
		lbpp = 16;
		lgray = 0;
		break;
	default:
		dev_dbg(dev, "unsupported LDDFR bit depth.\n");
		return -EINVAL;
	}

	if (bpp)
		*bpp = lbpp;
	if (gray)
		*gray = lgray;

	return 0;
}