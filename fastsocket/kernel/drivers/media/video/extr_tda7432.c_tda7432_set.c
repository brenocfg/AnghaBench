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
struct v4l2_subdev {int dummy; } ;
struct tda7432 {unsigned char input; unsigned char volume; unsigned char bass; unsigned char treble; unsigned char lf; unsigned char lr; unsigned char rf; unsigned char rr; unsigned char loud; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 unsigned char TDA7432_IN ; 
 int /*<<< orphan*/  debug ; 
 int i2c_master_send (struct i2c_client*,unsigned char*,int) ; 
 struct tda7432* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_subdev*,char*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int tda7432_set(struct v4l2_subdev *sd)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct tda7432 *t = to_state(sd);
	unsigned char buf[16];

	v4l2_dbg(1, debug, sd,
		"tda7432: 7432_set(0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x)\n",
		t->input, t->volume, t->bass, t->treble, t->lf, t->lr,
		t->rf, t->rr, t->loud);
	buf[0]  = TDA7432_IN;
	buf[1]  = t->input;
	buf[2]  = t->volume;
	buf[3]  = t->bass;
	buf[4]	= t->treble;
	buf[5]  = t->lf;
	buf[6]  = t->lr;
	buf[7]  = t->rf;
	buf[8]  = t->rr;
	buf[9]  = t->loud;
	if (10 != i2c_master_send(client, buf, 10)) {
		v4l2_err(sd, "I/O error, trying tda7432_set\n");
		return -1;
	}

	return 0;
}