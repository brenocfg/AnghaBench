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
struct go7007 {int height; scalar_t__ format; int width; scalar_t__ interlace_coding; scalar_t__ dvd_mode; } ;
typedef  enum mpeg_frame_type { ____Placeholder_mpeg_frame_type } mpeg_frame_type ;

/* Variables and functions */
#define  BFRAME_BIDIR 131 
#define  BFRAME_POST 130 
#define  BFRAME_PRE 129 
 int /*<<< orphan*/  CODE_ADD (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CODE_GEN (int /*<<< orphan*/ ,unsigned char*) ; 
 int CODE_LENGTH (int /*<<< orphan*/ ) ; 
 scalar_t__ GO7007_FORMAT_MPEG2 ; 
#define  PFRAME 128 
 int** addrinctab ; 
 int /*<<< orphan*/  c ; 

__attribute__((used)) static int mpeg1_frame_header(struct go7007 *go, unsigned char *buf,
		int modulo, int pict_struct, enum mpeg_frame_type frame)
{
	int i, j, mb_code, mb_len;
	int rows = go->interlace_coding ? go->height / 32 : go->height / 16;
	CODE_GEN(c, buf + 6);

	switch (frame) {
	case PFRAME:
		mb_code = 0x1;
		mb_len = 3;
		break;
	case BFRAME_PRE:
		mb_code = 0x2;
		mb_len = 4;
		break;
	case BFRAME_POST:
		mb_code = 0x2;
		mb_len = 3;
		break;
	case BFRAME_BIDIR:
		mb_code = 0x2;
		mb_len = 2;
		break;
	default: /* keep the compiler happy */
		mb_code = mb_len = 0;
		break;
	}

	CODE_ADD(c, frame == PFRAME ? 0x2 : 0x3, 13);
	CODE_ADD(c, 0xffff, 16);
	CODE_ADD(c, go->format == GO7007_FORMAT_MPEG2 ? 0x7 : 0x4, 4);
	if (frame != PFRAME)
		CODE_ADD(c, go->format == GO7007_FORMAT_MPEG2 ? 0x7 : 0x4, 4);
	else
		CODE_ADD(c, 0, 4); /* Is this supposed to be here?? */
	CODE_ADD(c, 0, 3); /* What is this?? */
	/* Byte-align with zeros */
	j = 8 - (CODE_LENGTH(c) % 8);
	if (j != 8)
		CODE_ADD(c, 0, j);

	if (go->format == GO7007_FORMAT_MPEG2) {
		CODE_ADD(c, 0x1, 24);
		CODE_ADD(c, 0xb5, 8);
		CODE_ADD(c, 0x844, 12);
		CODE_ADD(c, frame == PFRAME ? 0xff : 0x44, 8);
		if (go->interlace_coding) {
			CODE_ADD(c, pict_struct, 4);
			if (go->dvd_mode)
				CODE_ADD(c, 0x000, 11);
			else
				CODE_ADD(c, 0x200, 11);
		} else {
			CODE_ADD(c, 0x3, 4);
			CODE_ADD(c, 0x20c, 11);
		}
		/* Byte-align with zeros */
		j = 8 - (CODE_LENGTH(c) % 8);
		if (j != 8)
			CODE_ADD(c, 0, j);
	}

	for (i = 0; i < rows; ++i) {
		CODE_ADD(c, 1, 24);
		CODE_ADD(c, i + 1, 8);
		CODE_ADD(c, 0x2, 6);
		CODE_ADD(c, 0x1, 1);
		CODE_ADD(c, mb_code, mb_len);
		if (go->interlace_coding) {
			CODE_ADD(c, 0x1, 2);
			CODE_ADD(c, pict_struct == 1 ? 0x0 : 0x1, 1);
		}
		if (frame == BFRAME_BIDIR) {
			CODE_ADD(c, 0x3, 2);
			if (go->interlace_coding)
				CODE_ADD(c, pict_struct == 1 ? 0x0 : 0x1, 1);
		}
		CODE_ADD(c, 0x3, 2);
		for (j = (go->width >> 4) - 2; j >= 33; j -= 33)
			CODE_ADD(c, 0x8, 11);
		CODE_ADD(c, addrinctab[j][0], addrinctab[j][1]);
		CODE_ADD(c, mb_code, mb_len);
		if (go->interlace_coding) {
			CODE_ADD(c, 0x1, 2);
			CODE_ADD(c, pict_struct == 1 ? 0x0 : 0x1, 1);
		}
		if (frame == BFRAME_BIDIR) {
			CODE_ADD(c, 0x3, 2);
			if (go->interlace_coding)
				CODE_ADD(c, pict_struct == 1 ? 0x0 : 0x1, 1);
		}
		CODE_ADD(c, 0x3, 2);

		/* Byte-align with zeros */
		j = 8 - (CODE_LENGTH(c) % 8);
		if (j != 8)
			CODE_ADD(c, 0, j);
	}

	i = CODE_LENGTH(c) + 4 * 8;
	buf[2] = 0x00;
	buf[3] = 0x00;
	buf[4] = 0x01;
	buf[5] = 0x00;
	return i;
}