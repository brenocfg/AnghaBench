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
typedef  int u8 ;
struct v4l2_tuner {int signal; int capability; int rxsubchans; int /*<<< orphan*/  audmode; } ;
struct v4l2_subdev {int dummy; } ;
struct cx18_av_state {int /*<<< orphan*/  audmode; scalar_t__ radio; } ;
struct cx18 {int dummy; } ;

/* Variables and functions */
 int V4L2_TUNER_CAP_LANG1 ; 
 int V4L2_TUNER_CAP_LANG2 ; 
 int V4L2_TUNER_CAP_SAP ; 
 int V4L2_TUNER_CAP_STEREO ; 
 int V4L2_TUNER_SUB_LANG1 ; 
 int V4L2_TUNER_SUB_LANG2 ; 
 int V4L2_TUNER_SUB_MONO ; 
 int V4L2_TUNER_SUB_SAP ; 
 int V4L2_TUNER_SUB_STEREO ; 
 int cx18_av_read (struct cx18*,int) ; 
 struct cx18_av_state* to_cx18_av_state (struct v4l2_subdev*) ; 
 struct cx18* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int cx18_av_g_tuner(struct v4l2_subdev *sd, struct v4l2_tuner *vt)
{
	struct cx18_av_state *state = to_cx18_av_state(sd);
	struct cx18 *cx = v4l2_get_subdevdata(sd);
	u8 vpres;
	u8 mode;
	int val = 0;

	if (state->radio)
		return 0;

	vpres = cx18_av_read(cx, 0x40e) & 0x20;
	vt->signal = vpres ? 0xffff : 0x0;

	vt->capability |=
		    V4L2_TUNER_CAP_STEREO | V4L2_TUNER_CAP_LANG1 |
		    V4L2_TUNER_CAP_LANG2 | V4L2_TUNER_CAP_SAP;

	mode = cx18_av_read(cx, 0x804);

	/* get rxsubchans and audmode */
	if ((mode & 0xf) == 1)
		val |= V4L2_TUNER_SUB_STEREO;
	else
		val |= V4L2_TUNER_SUB_MONO;

	if (mode == 2 || mode == 4)
		val = V4L2_TUNER_SUB_LANG1 | V4L2_TUNER_SUB_LANG2;

	if (mode & 0x10)
		val |= V4L2_TUNER_SUB_SAP;

	vt->rxsubchans = val;
	vt->audmode = state->audmode;
	return 0;
}