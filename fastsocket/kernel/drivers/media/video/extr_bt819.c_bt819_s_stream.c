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
struct bt819 {int enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  bt819_setbit (struct bt819*,int,int,int) ; 
 int /*<<< orphan*/  debug ; 
 struct bt819* to_bt819 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int) ; 

__attribute__((used)) static int bt819_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct bt819 *decoder = to_bt819(sd);

	v4l2_dbg(1, debug, sd, "enable output %x\n", enable);

	if (decoder->enable != enable) {
		decoder->enable = enable;
		bt819_setbit(decoder, 0x16, 7, !enable);
	}
	return 0;
}