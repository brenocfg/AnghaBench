#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct v4l2_decode_vbi_line {int* p; int line; int /*<<< orphan*/  is_second_field; scalar_t__ type; } ;
struct TYPE_4__ {int sliced_decoder_line_size; TYPE_1__* sliced_data; } ;
struct ivtv {TYPE_2__ vbi; int /*<<< orphan*/  sd_video; } ;
struct TYPE_3__ {int line; int /*<<< orphan*/  data; int /*<<< orphan*/  field; scalar_t__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  decode_vbi_line ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  v4l2_subdev_call (int /*<<< orphan*/ ,struct v4l2_decode_vbi_line,int /*<<< orphan*/ ,struct v4l2_decode_vbi_line*) ; 

__attribute__((used)) static u32 compress_sliced_buf(struct ivtv *itv, u32 line, u8 *buf, u32 size, u8 sav)
{
	u32 line_size = itv->vbi.sliced_decoder_line_size;
	struct v4l2_decode_vbi_line vbi;
	int i;
	unsigned lines = 0;

	/* find the first valid line */
	for (i = 0; i < size; i++, buf++) {
		if (buf[0] == 0xff && !buf[1] && !buf[2] && buf[3] == sav)
			break;
	}

	size -= i;
	if (size < line_size) {
		return line;
	}
	for (i = 0; i < size / line_size; i++) {
		u8 *p = buf + i * line_size;

		/* Look for SAV code  */
		if (p[0] != 0xff || p[1] || p[2] || p[3] != sav) {
			continue;
		}
		vbi.p = p + 4;
		v4l2_subdev_call(itv->sd_video, vbi, decode_vbi_line, &vbi);
		if (vbi.type && !(lines & (1 << vbi.line))) {
			lines |= 1 << vbi.line;
			itv->vbi.sliced_data[line].id = vbi.type;
			itv->vbi.sliced_data[line].field = vbi.is_second_field;
			itv->vbi.sliced_data[line].line = vbi.line;
			memcpy(itv->vbi.sliced_data[line].data, vbi.p, 42);
			line++;
		}
	}
	return line;
}