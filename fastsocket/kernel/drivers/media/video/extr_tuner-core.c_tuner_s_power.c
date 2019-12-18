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
struct v4l2_subdev {int dummy; } ;
struct analog_demod_ops {int /*<<< orphan*/  (* standby ) (TYPE_2__*) ;} ;
struct TYPE_3__ {struct analog_demod_ops analog_ops; } ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct tuner {int standby; TYPE_2__ fe; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 struct tuner* to_tuner (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  tuner_dbg (char*) ; 

__attribute__((used)) static int tuner_s_power(struct v4l2_subdev *sd, int on)
{
	struct tuner *t = to_tuner(sd);
	struct analog_demod_ops *analog_ops = &t->fe.ops.analog_ops;

	/* FIXME: Why this function don't wake the tuner if on != 0 ? */
	if (on)
		return 0;

	tuner_dbg("Putting tuner to sleep\n");
	t->standby = true;
	if (analog_ops->standby)
		analog_ops->standby(&t->fe);
	return 0;
}