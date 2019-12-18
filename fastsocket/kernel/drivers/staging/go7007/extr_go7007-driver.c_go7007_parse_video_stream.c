#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct go7007 {int format; int state; int seen_frame; int parse_length; int modet_word; int /*<<< orphan*/  spinlock; TYPE_1__* active_buf; int /*<<< orphan*/  active_map; int /*<<< orphan*/  video_dev; } ;
struct TYPE_2__ {int bytesused; int modet_active; int /*<<< orphan*/  offset; int /*<<< orphan*/  frame_offset; } ;

/* Variables and functions */
 int GO7007_BUF_SIZE ; 
 int const GO7007_FORMAT_MJPEG ; 
#define  GO7007_FORMAT_MPEG1 139 
#define  GO7007_FORMAT_MPEG2 138 
#define  GO7007_FORMAT_MPEG4 137 
#define  STATE_00 136 
#define  STATE_00_00 135 
#define  STATE_00_00_01 134 
#define  STATE_DATA 133 
#define  STATE_FF 132 
#define  STATE_MODET_MAP 131 
#define  STATE_UNPARSED 130 
#define  STATE_VBI_LEN_A 129 
#define  STATE_VBI_LEN_B 128 
 int /*<<< orphan*/  frame_boundary (struct go7007*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  store_byte (TYPE_1__*,int) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  write_bitmap_word (struct go7007*) ; 

void go7007_parse_video_stream(struct go7007 *go, u8 *buf, int length)
{
	int i, seq_start_code = -1, frame_start_code = -1;

	spin_lock(&go->spinlock);

	switch (go->format) {
	case GO7007_FORMAT_MPEG4:
		seq_start_code = 0xB0;
		frame_start_code = 0xB6;
		break;
	case GO7007_FORMAT_MPEG1:
	case GO7007_FORMAT_MPEG2:
		seq_start_code = 0xB3;
		frame_start_code = 0x00;
		break;
	}

	for (i = 0; i < length; ++i) {
		if (go->active_buf != NULL &&
			    go->active_buf->bytesused >= GO7007_BUF_SIZE - 3) {
			v4l2_info(go->video_dev, "dropping oversized frame\n");
			go->active_buf->offset -= go->active_buf->bytesused;
			go->active_buf->bytesused = 0;
			go->active_buf->modet_active = 0;
			go->active_buf = NULL;
		}

		switch (go->state) {
		case STATE_DATA:
			switch (buf[i]) {
			case 0x00:
				go->state = STATE_00;
				break;
			case 0xFF:
				go->state = STATE_FF;
				break;
			default:
				store_byte(go->active_buf, buf[i]);
				break;
			}
			break;
		case STATE_00:
			switch (buf[i]) {
			case 0x00:
				go->state = STATE_00_00;
				break;
			case 0xFF:
				store_byte(go->active_buf, 0x00);
				go->state = STATE_FF;
				break;
			default:
				store_byte(go->active_buf, 0x00);
				store_byte(go->active_buf, buf[i]);
				go->state = STATE_DATA;
				break;
			}
			break;
		case STATE_00_00:
			switch (buf[i]) {
			case 0x00:
				store_byte(go->active_buf, 0x00);
				/* go->state remains STATE_00_00 */
				break;
			case 0x01:
				go->state = STATE_00_00_01;
				break;
			case 0xFF:
				store_byte(go->active_buf, 0x00);
				store_byte(go->active_buf, 0x00);
				go->state = STATE_FF;
				break;
			default:
				store_byte(go->active_buf, 0x00);
				store_byte(go->active_buf, 0x00);
				store_byte(go->active_buf, buf[i]);
				go->state = STATE_DATA;
				break;
			}
			break;
		case STATE_00_00_01:
			/* If this is the start of a new MPEG frame,
			 * get a new buffer */
			if ((go->format == GO7007_FORMAT_MPEG1 ||
					go->format == GO7007_FORMAT_MPEG2 ||
					go->format == GO7007_FORMAT_MPEG4) &&
					(buf[i] == seq_start_code ||
						buf[i] == 0xB8 || /* GOP code */
						buf[i] == frame_start_code)) {
				if (go->active_buf == NULL || go->seen_frame)
					frame_boundary(go);
				if (buf[i] == frame_start_code) {
					if (go->active_buf != NULL)
						go->active_buf->frame_offset =
							go->active_buf->offset;
					go->seen_frame = 1;
				} else {
					go->seen_frame = 0;
				}
			}
			/* Handle any special chunk types, or just write the
			 * start code to the (potentially new) buffer */
			switch (buf[i]) {
			case 0xF5: /* timestamp */
				go->parse_length = 12;
				go->state = STATE_UNPARSED;
				break;
			case 0xF6: /* vbi */
				go->state = STATE_VBI_LEN_A;
				break;
			case 0xF8: /* MD map */
				go->parse_length = 0;
				memset(go->active_map, 0,
						sizeof(go->active_map));
				go->state = STATE_MODET_MAP;
				break;
			case 0xFF: /* Potential JPEG start code */
				store_byte(go->active_buf, 0x00);
				store_byte(go->active_buf, 0x00);
				store_byte(go->active_buf, 0x01);
				go->state = STATE_FF;
				break;
			default:
				store_byte(go->active_buf, 0x00);
				store_byte(go->active_buf, 0x00);
				store_byte(go->active_buf, 0x01);
				store_byte(go->active_buf, buf[i]);
				go->state = STATE_DATA;
				break;
			}
			break;
		case STATE_FF:
			switch (buf[i]) {
			case 0x00:
				store_byte(go->active_buf, 0xFF);
				go->state = STATE_00;
				break;
			case 0xFF:
				store_byte(go->active_buf, 0xFF);
				/* go->state remains STATE_FF */
				break;
			case 0xD8:
				if (go->format == GO7007_FORMAT_MJPEG)
					frame_boundary(go);
				/* fall through */
			default:
				store_byte(go->active_buf, 0xFF);
				store_byte(go->active_buf, buf[i]);
				go->state = STATE_DATA;
				break;
			}
			break;
		case STATE_VBI_LEN_A:
			go->parse_length = buf[i] << 8;
			go->state = STATE_VBI_LEN_B;
			break;
		case STATE_VBI_LEN_B:
			go->parse_length |= buf[i];
			if (go->parse_length > 0)
				go->state = STATE_UNPARSED;
			else
				go->state = STATE_DATA;
			break;
		case STATE_MODET_MAP:
			if (go->parse_length < 204) {
				if (go->parse_length & 1) {
					go->modet_word |= buf[i];
					write_bitmap_word(go);
				} else
					go->modet_word = buf[i] << 8;
			} else if (go->parse_length == 207 && go->active_buf) {
				go->active_buf->modet_active = buf[i];
			}
			if (++go->parse_length == 208)
				go->state = STATE_DATA;
			break;
		case STATE_UNPARSED:
			if (--go->parse_length == 0)
				go->state = STATE_DATA;
			break;
		}
	}

	spin_unlock(&go->spinlock);
}