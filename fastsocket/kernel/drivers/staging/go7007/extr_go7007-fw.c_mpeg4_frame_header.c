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
struct go7007 {int width; int height; } ;
typedef  enum mpeg_frame_type { ____Placeholder_mpeg_frame_type } mpeg_frame_type ;

/* Variables and functions */
#define  BFRAME_BIDIR 132 
#define  BFRAME_EMPTY 131 
#define  BFRAME_POST 130 
#define  BFRAME_PRE 129 
 int /*<<< orphan*/  CODE_ADD (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CODE_GEN (int /*<<< orphan*/ ,unsigned char*) ; 
 int CODE_LENGTH (int /*<<< orphan*/ ) ; 
#define  PFRAME 128 
 int /*<<< orphan*/  c ; 
 int vti_bitlen (struct go7007*) ; 

__attribute__((used)) static int mpeg4_frame_header(struct go7007 *go, unsigned char *buf,
		int modulo, enum mpeg_frame_type frame)
{
	int i;
	CODE_GEN(c, buf + 6);
	int mb_count = (go->width >> 4) * (go->height >> 4);

	CODE_ADD(c, frame == PFRAME ? 0x1 : 0x2, 2);
	if (modulo)
		CODE_ADD(c, 0x1, 1);
	CODE_ADD(c, 0x1, 2);
	CODE_ADD(c, 0, vti_bitlen(go));
	CODE_ADD(c, 0x3, 2);
	if (frame == PFRAME)
		CODE_ADD(c, 0, 1);
	CODE_ADD(c, 0xc, 11);
	if (frame != PFRAME)
		CODE_ADD(c, 0x4, 3);
	if (frame != BFRAME_EMPTY) {
		for (i = 0; i < mb_count; ++i) {
			switch (frame) {
			case PFRAME:
				CODE_ADD(c, 0x1, 1);
				break;
			case BFRAME_PRE:
				CODE_ADD(c, 0x47, 8);
				break;
			case BFRAME_POST:
				CODE_ADD(c, 0x27, 7);
				break;
			case BFRAME_BIDIR:
				CODE_ADD(c, 0x5f, 8);
				break;
			case BFRAME_EMPTY: /* keep compiler quiet */
				break;
			}
		}
	}

	/* Byte-align with a zero followed by ones */
	i = 8 - (CODE_LENGTH(c) % 8);
	CODE_ADD(c, 0, 1);
	CODE_ADD(c, (1 << (i - 1)) - 1, i - 1);

	i = CODE_LENGTH(c) + 4 * 8;
	buf[0] = i & 0xff;
	buf[1] = i >> 8;
	buf[2] = 0x00;
	buf[3] = 0x00;
	buf[4] = 0x01;
	buf[5] = 0xb6;
	return i;
}