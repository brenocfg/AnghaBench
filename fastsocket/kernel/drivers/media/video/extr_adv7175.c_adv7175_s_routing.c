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
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;
struct adv7175 {int norm; int input; } ;

/* Variables and functions */
 int EINVAL ; 
 int TR0MODE ; 
 int TR0RST ; 
 int TR1CAPT ; 
 int TR1PLAY ; 
 int V4L2_STD_NTSC ; 
 int V4L2_STD_SECAM ; 
 int /*<<< orphan*/  adv7175_write (struct v4l2_subdev*,int,int) ; 
 int /*<<< orphan*/  debug ; 
 int* inputs ; 
 int /*<<< orphan*/  set_subcarrier_freq (struct v4l2_subdev*,int) ; 
 struct adv7175* to_adv7175 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int) ; 

__attribute__((used)) static int adv7175_s_routing(struct v4l2_subdev *sd,
			     u32 input, u32 output, u32 config)
{
	struct adv7175 *encoder = to_adv7175(sd);

	/* RJ: input = 0: input is from decoder
	   input = 1: input is from ZR36060
	   input = 2: color bar */

	switch (input) {
	case 0:
		adv7175_write(sd, 0x01, 0x00);

		if (encoder->norm & V4L2_STD_NTSC)
			set_subcarrier_freq(sd, 1);

		adv7175_write(sd, 0x0c, TR1CAPT);	/* TR1 */
		if (encoder->norm & V4L2_STD_SECAM)
			adv7175_write(sd, 0x0d, 0x49);	/* Disable genlock */
		else
			adv7175_write(sd, 0x0d, 0x4f);	/* Enable genlock */
		adv7175_write(sd, 0x07, TR0MODE | TR0RST);
		adv7175_write(sd, 0x07, TR0MODE);
		/*udelay(10);*/
		break;

	case 1:
		adv7175_write(sd, 0x01, 0x00);

		if (encoder->norm & V4L2_STD_NTSC)
			set_subcarrier_freq(sd, 0);

		adv7175_write(sd, 0x0c, TR1PLAY);	/* TR1 */
		adv7175_write(sd, 0x0d, 0x49);
		adv7175_write(sd, 0x07, TR0MODE | TR0RST);
		adv7175_write(sd, 0x07, TR0MODE);
		/* udelay(10); */
		break;

	case 2:
		adv7175_write(sd, 0x01, 0x80);

		if (encoder->norm & V4L2_STD_NTSC)
			set_subcarrier_freq(sd, 0);

		adv7175_write(sd, 0x0d, 0x49);
		adv7175_write(sd, 0x07, TR0MODE | TR0RST);
		adv7175_write(sd, 0x07, TR0MODE);
		/* udelay(10); */
		break;

	default:
		v4l2_dbg(1, debug, sd, "illegal input: %d\n", input);
		return -EINVAL;
	}
	v4l2_dbg(1, debug, sd, "switched to %s\n", inputs[input]);
	encoder->input = input;
	return 0;
}