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
struct TYPE_4__ {scalar_t__ sample_pixel; scalar_t__ sample_ln; scalar_t__ b_clamp_enable; } ;
struct TYPE_3__ {scalar_t__ gama_wd; scalar_t__ enable; } ;
struct ccdc_config_params_raw {scalar_t__ datasft; scalar_t__ mfilt1; scalar_t__ mfilt2; scalar_t__ med_filt_thres; scalar_t__ data_sz; TYPE_2__ blk_clamp; TYPE_1__ alaw; } ;

/* Variables and functions */
 scalar_t__ CCDC_DATA_16BITS ; 
 scalar_t__ CCDC_DATA_8BITS ; 
 scalar_t__ CCDC_DATA_NO_SHIFT ; 
 scalar_t__ CCDC_DATA_SHIFT_6BIT ; 
 scalar_t__ CCDC_GAMMA_BITS_09_0 ; 
 scalar_t__ CCDC_GAMMA_BITS_13_4 ; 
 scalar_t__ CCDC_MEDIAN_FILTER1 ; 
 scalar_t__ CCDC_MEDIAN_FILTER2 ; 
 scalar_t__ CCDC_MED_FILT_THRESH ; 
 scalar_t__ CCDC_NO_MEDIAN_FILTER1 ; 
 scalar_t__ CCDC_NO_MEDIAN_FILTER2 ; 
 scalar_t__ CCDC_SAMPLE_16LINES ; 
 scalar_t__ CCDC_SAMPLE_16PIXELS ; 
 scalar_t__ CCDC_SAMPLE_1LINES ; 
 scalar_t__ CCDC_SAMPLE_1PIXELS ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int validate_ccdc_param(struct ccdc_config_params_raw *ccdcparam)
{
	if (ccdcparam->datasft < CCDC_DATA_NO_SHIFT ||
	    ccdcparam->datasft > CCDC_DATA_SHIFT_6BIT) {
		dev_dbg(dev, "Invalid value of data shift\n");
		return -EINVAL;
	}

	if (ccdcparam->mfilt1 < CCDC_NO_MEDIAN_FILTER1 ||
	    ccdcparam->mfilt1 > CCDC_MEDIAN_FILTER1) {
		dev_dbg(dev, "Invalid value of median filter1\n");
		return -EINVAL;
	}

	if (ccdcparam->mfilt2 < CCDC_NO_MEDIAN_FILTER2 ||
	    ccdcparam->mfilt2 > CCDC_MEDIAN_FILTER2) {
		dev_dbg(dev, "Invalid value of median filter2\n");
		return -EINVAL;
	}

	if ((ccdcparam->med_filt_thres < 0) ||
	   (ccdcparam->med_filt_thres > CCDC_MED_FILT_THRESH)) {
		dev_dbg(dev, "Invalid value of median filter thresold\n");
		return -EINVAL;
	}

	if (ccdcparam->data_sz < CCDC_DATA_16BITS ||
	    ccdcparam->data_sz > CCDC_DATA_8BITS) {
		dev_dbg(dev, "Invalid value of data size\n");
		return -EINVAL;
	}

	if (ccdcparam->alaw.enable) {
		if (ccdcparam->alaw.gama_wd < CCDC_GAMMA_BITS_13_4 ||
		    ccdcparam->alaw.gama_wd > CCDC_GAMMA_BITS_09_0) {
			dev_dbg(dev, "Invalid value of ALAW\n");
			return -EINVAL;
		}
	}

	if (ccdcparam->blk_clamp.b_clamp_enable) {
		if (ccdcparam->blk_clamp.sample_pixel < CCDC_SAMPLE_1PIXELS ||
		    ccdcparam->blk_clamp.sample_pixel > CCDC_SAMPLE_16PIXELS) {
			dev_dbg(dev, "Invalid value of sample pixel\n");
			return -EINVAL;
		}
		if (ccdcparam->blk_clamp.sample_ln < CCDC_SAMPLE_1LINES ||
		    ccdcparam->blk_clamp.sample_ln > CCDC_SAMPLE_16LINES) {
			dev_dbg(dev, "Invalid value of sample lines\n");
			return -EINVAL;
		}
	}
	return 0;
}