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
struct v4l2_control {int id; int value; } ;
struct TYPE_2__ {int id; int /*<<< orphan*/  name; } ;
struct cx88_ctrl {int off; int shift; int mask; scalar_t__ sreg; int /*<<< orphan*/  reg; TYPE_1__ v; } ;
struct cx88_core {int dummy; } ;

/* Variables and functions */
 int CX8800_CTLS ; 
 int EINVAL ; 
#define  V4L2_CID_AUDIO_BALANCE 129 
#define  V4L2_CID_AUDIO_VOLUME 128 
 struct cx88_ctrl* cx8800_ctls ; 
 int cx_read (int /*<<< orphan*/ ) ; 
 int cx_sread (scalar_t__) ; 
 int /*<<< orphan*/  dprintk (int,char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,char*) ; 
 scalar_t__ unlikely (int) ; 

int cx88_get_control (struct cx88_core  *core, struct v4l2_control *ctl)
{
	struct cx88_ctrl  *c    = NULL;
	u32 value;
	int i;

	for (i = 0; i < CX8800_CTLS; i++)
		if (cx8800_ctls[i].v.id == ctl->id)
			c = &cx8800_ctls[i];
	if (unlikely(NULL == c))
		return -EINVAL;

	value = c->sreg ? cx_sread(c->sreg) : cx_read(c->reg);
	switch (ctl->id) {
	case V4L2_CID_AUDIO_BALANCE:
		ctl->value = ((value & 0x7f) < 0x40) ? ((value & 0x7f) + 0x40)
					: (0x7f - (value & 0x7f));
		break;
	case V4L2_CID_AUDIO_VOLUME:
		ctl->value = 0x3f - (value & 0x3f);
		break;
	default:
		ctl->value = ((value + (c->off << c->shift)) & c->mask) >> c->shift;
		break;
	}
	dprintk(1,"get_control id=0x%X(%s) ctrl=0x%02x, reg=0x%02x val=0x%02x (mask 0x%02x)%s\n",
				ctl->id, c->v.name, ctl->value, c->reg,
				value,c->mask, c->sreg ? " [shadowed]" : "");
	return 0;
}