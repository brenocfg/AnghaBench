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
struct saa7185 {int* reg; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  saa7185_write (struct v4l2_subdev*,int,int) ; 
 struct saa7185* to_saa7185 (struct v4l2_subdev*) ; 

__attribute__((used)) static int saa7185_s_routing(struct v4l2_subdev *sd,
			     u32 input, u32 output, u32 config)
{
	struct saa7185 *encoder = to_saa7185(sd);

	/* RJ: input = 0: input is from SA7111
	 input = 1: input is from ZR36060 */

	switch (input) {
	case 0:
		/* turn off colorbar */
		saa7185_write(sd, 0x3a, 0x0f);
		/* Switch RTCE to 1 */
		saa7185_write(sd, 0x61, (encoder->reg[0x61] & 0xf7) | 0x08);
		saa7185_write(sd, 0x6e, 0x01);
		break;

	case 1:
		/* turn off colorbar */
		saa7185_write(sd, 0x3a, 0x0f);
		/* Switch RTCE to 0 */
		saa7185_write(sd, 0x61, (encoder->reg[0x61] & 0xf7) | 0x00);
		/* SW: a slight sync problem... */
		saa7185_write(sd, 0x6e, 0x00);
		break;

	case 2:
		/* turn on colorbar */
		saa7185_write(sd, 0x3a, 0x8f);
		/* Switch RTCE to 0 */
		saa7185_write(sd, 0x61, (encoder->reg[0x61] & 0xf7) | 0x08);
		/* SW: a slight sync problem... */
		saa7185_write(sd, 0x6e, 0x01);
		break;

	default:
		return -EINVAL;
	}
	return 0;
}