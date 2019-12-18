#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct radeon_i2c_bus_rec {int /*<<< orphan*/  mm_i2c; } ;
struct radeon_i2c_chan {struct radeon_i2c_bus_rec rec; TYPE_1__* dev; } ;
struct radeon_device {int family; } ;
struct i2c_msg {int dummy; } ;
struct i2c_adapter {int dummy; } ;
struct TYPE_2__ {struct radeon_device* dev_private; } ;

/* Variables and functions */
#define  CHIP_CEDAR 171 
#define  CHIP_CYPRESS 170 
#define  CHIP_HEMLOCK 169 
#define  CHIP_JUNIPER 168 
#define  CHIP_R100 167 
#define  CHIP_R200 166 
#define  CHIP_R300 165 
#define  CHIP_R350 164 
#define  CHIP_R420 163 
#define  CHIP_R423 162 
#define  CHIP_R520 161 
#define  CHIP_R580 160 
#define  CHIP_R600 159 
#define  CHIP_REDWOOD 158 
#define  CHIP_RS100 157 
#define  CHIP_RS200 156 
#define  CHIP_RS300 155 
#define  CHIP_RS400 154 
#define  CHIP_RS480 153 
#define  CHIP_RS600 152 
#define  CHIP_RS690 151 
#define  CHIP_RS740 150 
#define  CHIP_RS780 149 
#define  CHIP_RS880 148 
#define  CHIP_RV100 147 
#define  CHIP_RV200 146 
#define  CHIP_RV250 145 
#define  CHIP_RV280 144 
#define  CHIP_RV350 143 
#define  CHIP_RV380 142 
#define  CHIP_RV410 141 
#define  CHIP_RV515 140 
#define  CHIP_RV530 139 
#define  CHIP_RV560 138 
#define  CHIP_RV570 137 
#define  CHIP_RV610 136 
#define  CHIP_RV620 135 
#define  CHIP_RV630 134 
#define  CHIP_RV635 133 
#define  CHIP_RV670 132 
#define  CHIP_RV710 131 
#define  CHIP_RV730 130 
#define  CHIP_RV740 129 
#define  CHIP_RV770 128 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EIO ; 
 struct radeon_i2c_chan* i2c_get_adapdata (struct i2c_adapter*) ; 
 int r100_hw_i2c_xfer (struct i2c_adapter*,struct i2c_msg*,int) ; 
 int r500_hw_i2c_xfer (struct i2c_adapter*,struct i2c_msg*,int) ; 

__attribute__((used)) static int radeon_hw_i2c_xfer(struct i2c_adapter *i2c_adap,
			      struct i2c_msg *msgs, int num)
{
	struct radeon_i2c_chan *i2c = i2c_get_adapdata(i2c_adap);
	struct radeon_device *rdev = i2c->dev->dev_private;
	struct radeon_i2c_bus_rec *rec = &i2c->rec;
	int ret = 0;

	switch (rdev->family) {
	case CHIP_R100:
	case CHIP_RV100:
	case CHIP_RS100:
	case CHIP_RV200:
	case CHIP_RS200:
	case CHIP_R200:
	case CHIP_RV250:
	case CHIP_RS300:
	case CHIP_RV280:
	case CHIP_R300:
	case CHIP_R350:
	case CHIP_RV350:
	case CHIP_RV380:
	case CHIP_R420:
	case CHIP_R423:
	case CHIP_RV410:
	case CHIP_RS400:
	case CHIP_RS480:
		ret = r100_hw_i2c_xfer(i2c_adap, msgs, num);
		break;
	case CHIP_RS600:
	case CHIP_RS690:
	case CHIP_RS740:
		/* XXX fill in hw i2c implementation */
		break;
	case CHIP_RV515:
	case CHIP_R520:
	case CHIP_RV530:
	case CHIP_RV560:
	case CHIP_RV570:
	case CHIP_R580:
		if (rec->mm_i2c)
			ret = r100_hw_i2c_xfer(i2c_adap, msgs, num);
		else
			ret = r500_hw_i2c_xfer(i2c_adap, msgs, num);
		break;
	case CHIP_R600:
	case CHIP_RV610:
	case CHIP_RV630:
	case CHIP_RV670:
		/* XXX fill in hw i2c implementation */
		break;
	case CHIP_RV620:
	case CHIP_RV635:
	case CHIP_RS780:
	case CHIP_RS880:
	case CHIP_RV770:
	case CHIP_RV730:
	case CHIP_RV710:
	case CHIP_RV740:
		/* XXX fill in hw i2c implementation */
		break;
	case CHIP_CEDAR:
	case CHIP_REDWOOD:
	case CHIP_JUNIPER:
	case CHIP_CYPRESS:
	case CHIP_HEMLOCK:
		/* XXX fill in hw i2c implementation */
		break;
	default:
		DRM_ERROR("i2c: unhandled radeon chip\n");
		ret = -EIO;
		break;
	}

	return ret;
}