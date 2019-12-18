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
typedef  int /*<<< orphan*/  vbi_no_data_pattern ;
typedef  int u8 ;
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_decode_vbi_line {int* p; int is_second_field; int line; scalar_t__ type; } ;
struct saa711x_state {int std; } ;

/* Variables and functions */
 scalar_t__ V4L2_SLICED_CAPTION_525 ; 
 scalar_t__ V4L2_SLICED_TELETEXT_B ; 
 scalar_t__ V4L2_SLICED_VPS ; 
 scalar_t__ V4L2_SLICED_WSS_625 ; 
 int V4L2_STD_525_60 ; 
 int /*<<< orphan*/  memcmp (int*,char const*,int) ; 
 int /*<<< orphan*/  saa711x_decode_vps (int*,int*) ; 
 int saa711x_decode_wss (int*) ; 
 int /*<<< orphan*/  saa711x_odd_parity (int) ; 
 struct saa711x_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int saa711x_decode_vbi_line(struct v4l2_subdev *sd, struct v4l2_decode_vbi_line *vbi)
{
	struct saa711x_state *state = to_state(sd);
	static const char vbi_no_data_pattern[] = {
		0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0
	};
	u8 *p = vbi->p;
	u32 wss;
	int id1, id2;   /* the ID1 and ID2 bytes from the internal header */

	vbi->type = 0;  /* mark result as a failure */
	id1 = p[2];
	id2 = p[3];
	/* Note: the field bit is inverted for 60 Hz video */
	if (state->std & V4L2_STD_525_60)
		id1 ^= 0x40;

	/* Skip internal header, p now points to the start of the payload */
	p += 4;
	vbi->p = p;

	/* calculate field and line number of the VBI packet (1-23) */
	vbi->is_second_field = ((id1 & 0x40) != 0);
	vbi->line = (id1 & 0x3f) << 3;
	vbi->line |= (id2 & 0x70) >> 4;

	/* Obtain data type */
	id2 &= 0xf;

	/* If the VBI slicer does not detect any signal it will fill up
	   the payload buffer with 0xa0 bytes. */
	if (!memcmp(p, vbi_no_data_pattern, sizeof(vbi_no_data_pattern)))
		return 0;

	/* decode payloads */
	switch (id2) {
	case 1:
		vbi->type = V4L2_SLICED_TELETEXT_B;
		break;
	case 4:
		if (!saa711x_odd_parity(p[0]) || !saa711x_odd_parity(p[1]))
			return 0;
		vbi->type = V4L2_SLICED_CAPTION_525;
		break;
	case 5:
		wss = saa711x_decode_wss(p);
		if (wss == -1)
			return 0;
		p[0] = wss & 0xff;
		p[1] = wss >> 8;
		vbi->type = V4L2_SLICED_WSS_625;
		break;
	case 7:
		if (saa711x_decode_vps(p, p) != 0)
			return 0;
		vbi->type = V4L2_SLICED_VPS;
		break;
	default:
		break;
	}
	return 0;
}