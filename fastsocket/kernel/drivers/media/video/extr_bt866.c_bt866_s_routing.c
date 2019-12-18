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
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;
struct bt866 {int* reg; } ;
typedef  int __u8 ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  bt866_write (struct bt866*,int const,int const) ; 
 int /*<<< orphan*/  debug ; 
 struct bt866* to_bt866 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int) ; 

__attribute__((used)) static int bt866_s_routing(struct v4l2_subdev *sd,
			   u32 input, u32 output, u32 config)
{
	static const __u8 init[] = {
		0xc8, 0xcc, /* CRSCALE */
		0xca, 0x91, /* CBSCALE */
		0xcc, 0x24, /* YC16 | OSDNUM */
		0xda, 0x00, /*  */
		0xdc, 0x24, /* SETMODE | PAL */
		0xde, 0x02, /* EACTIVE */

		/* overlay colors */
		0x70, 0xEB, 0x90, 0x80, 0xB0, 0x80, /* white */
		0x72, 0xA2, 0x92, 0x8E, 0xB2, 0x2C, /* yellow */
		0x74, 0x83, 0x94, 0x2C, 0xB4, 0x9C, /* cyan */
		0x76, 0x70, 0x96, 0x3A, 0xB6, 0x48, /* green */
		0x78, 0x54, 0x98, 0xC6, 0xB8, 0xB8, /* magenta */
		0x7A, 0x41, 0x9A, 0xD4, 0xBA, 0x64, /* red */
		0x7C, 0x23, 0x9C, 0x72, 0xBC, 0xD4, /* blue */
		0x7E, 0x10, 0x9E, 0x80, 0xBE, 0x80, /* black */

		0x60, 0xEB, 0x80, 0x80, 0xc0, 0x80, /* white */
		0x62, 0xA2, 0x82, 0x8E, 0xc2, 0x2C, /* yellow */
		0x64, 0x83, 0x84, 0x2C, 0xc4, 0x9C, /* cyan */
		0x66, 0x70, 0x86, 0x3A, 0xc6, 0x48, /* green */
		0x68, 0x54, 0x88, 0xC6, 0xc8, 0xB8, /* magenta */
		0x6A, 0x41, 0x8A, 0xD4, 0xcA, 0x64, /* red */
		0x6C, 0x23, 0x8C, 0x72, 0xcC, 0xD4, /* blue */
		0x6E, 0x10, 0x8E, 0x80, 0xcE, 0x80, /* black */
	};
	struct bt866 *encoder = to_bt866(sd);
	u8 val;
	int i;

	for (i = 0; i < ARRAY_SIZE(init) / 2; i += 2)
		bt866_write(encoder, init[i], init[i+1]);

	val = encoder->reg[0xdc];

	if (input == 0)
		val |= 0x40; /* CBSWAP */
	else
		val &= ~0x40; /* !CBSWAP */

	bt866_write(encoder, 0xdc, val);

	val = encoder->reg[0xcc];
	if (input == 2)
		val |= 0x01; /* OSDBAR */
	else
		val &= ~0x01; /* !OSDBAR */
	bt866_write(encoder, 0xcc, val);

	v4l2_dbg(1, debug, sd, "set input %d\n", input);

	switch (input) {
	case 0:
	case 1:
	case 2:
		break;
	default:
		return -EINVAL;
	}
	return 0;
}