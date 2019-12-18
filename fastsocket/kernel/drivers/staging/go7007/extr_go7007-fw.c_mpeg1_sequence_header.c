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
struct go7007 {scalar_t__ format; int aspect_ratio; scalar_t__ standard; int sensor_framerate; int width; int height; scalar_t__ interlace_coding; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODE_ADD (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CODE_GEN (int /*<<< orphan*/ ,unsigned char*) ; 
 int CODE_LENGTH (int /*<<< orphan*/ ) ; 
 scalar_t__ GO7007_FORMAT_MPEG1 ; 
 scalar_t__ GO7007_FORMAT_MPEG2 ; 
#define  GO7007_RATIO_16_9 129 
#define  GO7007_RATIO_4_3 128 
 scalar_t__ GO7007_STD_NTSC ; 
 int /*<<< orphan*/  c ; 

__attribute__((used)) static int mpeg1_sequence_header(struct go7007 *go, unsigned char *buf, int ext)
{
	int i, aspect_ratio, picture_rate;
	CODE_GEN(c, buf + 6);

	if (go->format == GO7007_FORMAT_MPEG1) {
		switch (go->aspect_ratio) {
		case GO7007_RATIO_4_3:
			aspect_ratio = go->standard == GO7007_STD_NTSC ? 3 : 2;
			break;
		case GO7007_RATIO_16_9:
			aspect_ratio = go->standard == GO7007_STD_NTSC ? 5 : 4;
			break;
		default:
			aspect_ratio = 1;
			break;
		}
	} else {
		switch (go->aspect_ratio) {
		case GO7007_RATIO_4_3:
			aspect_ratio = 2;
			break;
		case GO7007_RATIO_16_9:
			aspect_ratio = 3;
			break;
		default:
			aspect_ratio = 1;
			break;
		}
	}
	switch (go->sensor_framerate) {
	case 24000:
		picture_rate = 1;
		break;
	case 24024:
		picture_rate = 2;
		break;
	case 25025:
		picture_rate = go->interlace_coding ? 6 : 3;
		break;
	case 30000:
		picture_rate = go->interlace_coding ? 7 : 4;
		break;
	case 30030:
		picture_rate = go->interlace_coding ? 8 : 5;
		break;
	default:
		picture_rate = 5; /* 30 fps seems like a reasonable default */
		break;
	}

	CODE_ADD(c, go->width, 12);
	CODE_ADD(c, go->height, 12);
	CODE_ADD(c, aspect_ratio, 4);
	CODE_ADD(c, picture_rate, 4);
	CODE_ADD(c, go->format == GO7007_FORMAT_MPEG2 ? 20000 : 0x3ffff, 18);
	CODE_ADD(c, 1, 1);
	CODE_ADD(c, go->format == GO7007_FORMAT_MPEG2 ? 112 : 20, 10);
	CODE_ADD(c, 0, 3);

	/* Byte-align with zeros */
	i = 8 - (CODE_LENGTH(c) % 8);
	if (i != 8)
		CODE_ADD(c, 0, i);

	if (go->format == GO7007_FORMAT_MPEG2) {
		CODE_ADD(c, 0x1, 24);
		CODE_ADD(c, 0xb5, 8);
		CODE_ADD(c, 0x148, 12);
		if (go->interlace_coding)
			CODE_ADD(c, 0x20001, 20);
		else
			CODE_ADD(c, 0xa0001, 20);
		CODE_ADD(c, 0, 16);

		/* Byte-align with zeros */
		i = 8 - (CODE_LENGTH(c) % 8);
		if (i != 8)
			CODE_ADD(c, 0, i);

		if (ext) {
			CODE_ADD(c, 0x1, 24);
			CODE_ADD(c, 0xb52, 12);
			CODE_ADD(c, go->standard == GO7007_STD_NTSC ? 2 : 1, 3);
			CODE_ADD(c, 0x105, 9);
			CODE_ADD(c, 0x505, 16);
			CODE_ADD(c, go->width, 14);
			CODE_ADD(c, 1, 1);
			CODE_ADD(c, go->height, 14);

			/* Byte-align with zeros */
			i = 8 - (CODE_LENGTH(c) % 8);
			if (i != 8)
				CODE_ADD(c, 0, i);
		}
	}

	i = CODE_LENGTH(c) + 4 * 8;
	buf[0] = i & 0xff;
	buf[1] = i >> 8;
	buf[2] = 0x00;
	buf[3] = 0x00;
	buf[4] = 0x01;
	buf[5] = 0xb3;
	return i;
}