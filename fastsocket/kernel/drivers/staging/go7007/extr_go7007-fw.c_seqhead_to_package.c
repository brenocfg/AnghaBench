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
typedef  int u16 ;
struct go7007 {int sensor_framerate; int fps_scale; scalar_t__ interlace_coding; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int copy_packages (int /*<<< orphan*/ *,int*,int,int) ; 
 int vti_bitlen (struct go7007*) ; 

__attribute__((used)) static int seqhead_to_package(struct go7007 *go, __le16 *code, int space,
	int (*sequence_header_func)(struct go7007 *go,
		unsigned char *buf, int ext))
{
	int vop_time_increment_bitlength = vti_bitlen(go);
	int fps = go->sensor_framerate / go->fps_scale *
					(go->interlace_coding ? 2 : 1);
	unsigned char buf[40] = { };
	int len = sequence_header_func(go, buf, 1);
	u16 pack[] = {
		0x2006,		0,
		0xbf08,		fps,
		0xbf09,		0,
		0xbff2,		vop_time_increment_bitlength,
		0xbff3,		(1 << vop_time_increment_bitlength) - 1,
		0xbfe6,		0,
		0xbfe7,		(fps / 1000) << 8,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,

		0x2007,		0,
		0xc800,		buf[2] << 8 | buf[3],
		0xc801,		buf[4] << 8 | buf[5],
		0xc802,		buf[6] << 8 | buf[7],
		0xc803,		buf[8] << 8 | buf[9],
		0xc406,		64,
		0xc407,		len - 64,
		0xc61b,		1,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,

		0x200e,		0,
		0xc808,		buf[10] << 8 | buf[11],
		0xc809,		buf[12] << 8 | buf[13],
		0xc80a,		buf[14] << 8 | buf[15],
		0xc80b,		buf[16] << 8 | buf[17],
		0xc80c,		buf[18] << 8 | buf[19],
		0xc80d,		buf[20] << 8 | buf[21],
		0xc80e,		buf[22] << 8 | buf[23],
		0xc80f,		buf[24] << 8 | buf[25],
		0xc810,		buf[26] << 8 | buf[27],
		0xc811,		buf[28] << 8 | buf[29],
		0xc812,		buf[30] << 8 | buf[31],
		0xc813,		buf[32] << 8 | buf[33],
		0xc814,		buf[34] << 8 | buf[35],
		0xc815,		buf[36] << 8 | buf[37],
		0,		0,
		0,		0,
		0,		0,
	};

	return copy_packages(code, pack, 3, space);
}