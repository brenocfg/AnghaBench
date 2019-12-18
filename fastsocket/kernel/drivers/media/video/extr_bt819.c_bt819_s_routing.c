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
struct v4l2_subdev {TYPE_1__* v4l2_dev; } ;
struct bt819 {int input; } ;
struct TYPE_2__ {int /*<<< orphan*/ * notify; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT819_FIFO_RESET_HIGH ; 
 int /*<<< orphan*/  BT819_FIFO_RESET_LOW ; 
 int EINVAL ; 
 int /*<<< orphan*/  bt819_setbit (struct bt819*,int,int,int) ; 
 int /*<<< orphan*/  debug ; 
 struct bt819* to_bt819 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_subdev*,char*) ; 
 int /*<<< orphan*/  v4l2_subdev_notify (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bt819_s_routing(struct v4l2_subdev *sd,
			   u32 input, u32 output, u32 config)
{
	struct bt819 *decoder = to_bt819(sd);

	v4l2_dbg(1, debug, sd, "set input %x\n", input);

	if (input < 0 || input > 7)
		return -EINVAL;

	if (sd->v4l2_dev == NULL || sd->v4l2_dev->notify == NULL)
		v4l2_err(sd, "no notify found!\n");

	if (decoder->input != input) {
		v4l2_subdev_notify(sd, BT819_FIFO_RESET_LOW, 0);
		decoder->input = input;
		/* select mode */
		if (decoder->input == 0) {
			bt819_setbit(decoder, 0x0b, 6, 0);
			bt819_setbit(decoder, 0x1a, 1, 1);
		} else {
			bt819_setbit(decoder, 0x0b, 6, 1);
			bt819_setbit(decoder, 0x1a, 1, 0);
		}
		v4l2_subdev_notify(sd, BT819_FIFO_RESET_HIGH, 0);
	}
	return 0;
}