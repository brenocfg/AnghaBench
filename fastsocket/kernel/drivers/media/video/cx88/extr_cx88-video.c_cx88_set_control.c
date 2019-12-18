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
typedef  int u32 ;
struct v4l2_control {int id; scalar_t__ value; } ;
struct TYPE_2__ {int id; scalar_t__ minimum; scalar_t__ maximum; int /*<<< orphan*/  name; } ;
struct cx88_ctrl {int mask; int off; int shift; int /*<<< orphan*/  reg; scalar_t__ sreg; TYPE_1__ v; } ;
struct cx88_core {int tvnorm; } ;

/* Variables and functions */
 int CX8800_CTLS ; 
 int EINVAL ; 
#define  V4L2_CID_AUDIO_BALANCE 131 
#define  V4L2_CID_AUDIO_VOLUME 130 
#define  V4L2_CID_CHROMA_AGC 129 
#define  V4L2_CID_SATURATION 128 
 int V4L2_STD_SECAM ; 
 struct cx88_ctrl* cx8800_ctls ; 
 int /*<<< orphan*/  cx_andor (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cx_sandor (scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dprintk (int,char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,char*) ; 
 scalar_t__ unlikely (int) ; 

int cx88_set_control(struct cx88_core *core, struct v4l2_control *ctl)
{
	struct cx88_ctrl *c = NULL;
	u32 value,mask;
	int i;

	for (i = 0; i < CX8800_CTLS; i++) {
		if (cx8800_ctls[i].v.id == ctl->id) {
			c = &cx8800_ctls[i];
		}
	}
	if (unlikely(NULL == c))
		return -EINVAL;

	if (ctl->value < c->v.minimum)
		ctl->value = c->v.minimum;
	if (ctl->value > c->v.maximum)
		ctl->value = c->v.maximum;
	mask=c->mask;
	switch (ctl->id) {
	case V4L2_CID_AUDIO_BALANCE:
		value = (ctl->value < 0x40) ? (0x7f - ctl->value) : (ctl->value - 0x40);
		break;
	case V4L2_CID_AUDIO_VOLUME:
		value = 0x3f - (ctl->value & 0x3f);
		break;
	case V4L2_CID_SATURATION:
		/* special v_sat handling */

		value = ((ctl->value - c->off) << c->shift) & c->mask;

		if (core->tvnorm & V4L2_STD_SECAM) {
			/* For SECAM, both U and V sat should be equal */
			value=value<<8|value;
		} else {
			/* Keeps U Saturation proportional to V Sat */
			value=(value*0x5a)/0x7f<<8|value;
		}
		mask=0xffff;
		break;
	case V4L2_CID_CHROMA_AGC:
		/* Do not allow chroma AGC to be enabled for SECAM */
		value = ((ctl->value - c->off) << c->shift) & c->mask;
		if (core->tvnorm & V4L2_STD_SECAM && value)
			return -EINVAL;
		break;
	default:
		value = ((ctl->value - c->off) << c->shift) & c->mask;
		break;
	}
	dprintk(1,"set_control id=0x%X(%s) ctrl=0x%02x, reg=0x%02x val=0x%02x (mask 0x%02x)%s\n",
				ctl->id, c->v.name, ctl->value, c->reg, value,
				mask, c->sreg ? " [shadowed]" : "");
	if (c->sreg) {
		cx_sandor(c->sreg, c->reg, mask, value);
	} else {
		cx_andor(c->reg, mask, value);
	}
	return 0;
}