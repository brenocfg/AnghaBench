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
struct v4l2_control {int id; int /*<<< orphan*/  value; } ;
struct file {int dummy; } ;
struct bttv_fh {struct bttv* btv; } ;
struct bttv {int /*<<< orphan*/  opt_coring; int /*<<< orphan*/  opt_full_luma_range; int /*<<< orphan*/  opt_uv_ratio; int /*<<< orphan*/  opt_whitecrush_lower; int /*<<< orphan*/  opt_whitecrush_upper; int /*<<< orphan*/  opt_vcr_hack; int /*<<< orphan*/  opt_adc_crush; int /*<<< orphan*/  opt_automute; int /*<<< orphan*/  opt_lumafilter; int /*<<< orphan*/  opt_combfilter; int /*<<< orphan*/  opt_chroma_agc; int /*<<< orphan*/  saturation; int /*<<< orphan*/  contrast; int /*<<< orphan*/  hue; int /*<<< orphan*/  bright; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_AUDIO_BALANCE 147 
#define  V4L2_CID_AUDIO_BASS 146 
#define  V4L2_CID_AUDIO_MUTE 145 
#define  V4L2_CID_AUDIO_TREBLE 144 
#define  V4L2_CID_AUDIO_VOLUME 143 
#define  V4L2_CID_BRIGHTNESS 142 
#define  V4L2_CID_CONTRAST 141 
#define  V4L2_CID_HUE 140 
#define  V4L2_CID_PRIVATE_AGC_CRUSH 139 
#define  V4L2_CID_PRIVATE_AUTOMUTE 138 
#define  V4L2_CID_PRIVATE_CHROMA_AGC 137 
#define  V4L2_CID_PRIVATE_COMBFILTER 136 
#define  V4L2_CID_PRIVATE_CORING 135 
#define  V4L2_CID_PRIVATE_FULL_LUMA_RANGE 134 
#define  V4L2_CID_PRIVATE_LUMAFILTER 133 
#define  V4L2_CID_PRIVATE_UV_RATIO 132 
#define  V4L2_CID_PRIVATE_VCR_HACK 131 
#define  V4L2_CID_PRIVATE_WHITECRUSH_LOWER 130 
#define  V4L2_CID_PRIVATE_WHITECRUSH_UPPER 129 
#define  V4L2_CID_SATURATION 128 
 int /*<<< orphan*/  bttv_call_all (struct bttv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_control*) ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  g_ctrl ; 

__attribute__((used)) static int bttv_g_ctrl(struct file *file, void *priv,
					struct v4l2_control *c)
{
	struct bttv_fh *fh = priv;
	struct bttv *btv = fh->btv;

	switch (c->id) {
	case V4L2_CID_BRIGHTNESS:
		c->value = btv->bright;
		break;
	case V4L2_CID_HUE:
		c->value = btv->hue;
		break;
	case V4L2_CID_CONTRAST:
		c->value = btv->contrast;
		break;
	case V4L2_CID_SATURATION:
		c->value = btv->saturation;
		break;

	case V4L2_CID_AUDIO_MUTE:
	case V4L2_CID_AUDIO_VOLUME:
	case V4L2_CID_AUDIO_BALANCE:
	case V4L2_CID_AUDIO_BASS:
	case V4L2_CID_AUDIO_TREBLE:
		bttv_call_all(btv, core, g_ctrl, c);
		break;

	case V4L2_CID_PRIVATE_CHROMA_AGC:
		c->value = btv->opt_chroma_agc;
		break;
	case V4L2_CID_PRIVATE_COMBFILTER:
		c->value = btv->opt_combfilter;
		break;
	case V4L2_CID_PRIVATE_LUMAFILTER:
		c->value = btv->opt_lumafilter;
		break;
	case V4L2_CID_PRIVATE_AUTOMUTE:
		c->value = btv->opt_automute;
		break;
	case V4L2_CID_PRIVATE_AGC_CRUSH:
		c->value = btv->opt_adc_crush;
		break;
	case V4L2_CID_PRIVATE_VCR_HACK:
		c->value = btv->opt_vcr_hack;
		break;
	case V4L2_CID_PRIVATE_WHITECRUSH_UPPER:
		c->value = btv->opt_whitecrush_upper;
		break;
	case V4L2_CID_PRIVATE_WHITECRUSH_LOWER:
		c->value = btv->opt_whitecrush_lower;
		break;
	case V4L2_CID_PRIVATE_UV_RATIO:
		c->value = btv->opt_uv_ratio;
		break;
	case V4L2_CID_PRIVATE_FULL_LUMA_RANGE:
		c->value = btv->opt_full_luma_range;
		break;
	case V4L2_CID_PRIVATE_CORING:
		c->value = btv->opt_coring;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}