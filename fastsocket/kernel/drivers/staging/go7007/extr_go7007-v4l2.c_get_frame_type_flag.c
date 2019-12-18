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
typedef  int /*<<< orphan*/  u32 ;
struct go7007_buffer {int /*<<< orphan*/  frame_offset; int /*<<< orphan*/ * pages; } ;

/* Variables and functions */
#define  GO7007_FORMAT_MJPEG 131 
#define  GO7007_FORMAT_MPEG1 130 
#define  GO7007_FORMAT_MPEG2 129 
#define  GO7007_FORMAT_MPEG4 128 
 int /*<<< orphan*/  V4L2_BUF_FLAG_BFRAME ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_KEYFRAME ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_PFRAME ; 
 int* page_address (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 get_frame_type_flag(struct go7007_buffer *gobuf, int format)
{
	u8 *f = page_address(gobuf->pages[0]);

	switch (format) {
	case GO7007_FORMAT_MJPEG:
		return V4L2_BUF_FLAG_KEYFRAME;
	case GO7007_FORMAT_MPEG4:
		switch ((f[gobuf->frame_offset + 4] >> 6) & 0x3) {
		case 0:
			return V4L2_BUF_FLAG_KEYFRAME;
		case 1:
			return V4L2_BUF_FLAG_PFRAME;
		case 2:
			return V4L2_BUF_FLAG_BFRAME;
		default:
			return 0;
		}
	case GO7007_FORMAT_MPEG1:
	case GO7007_FORMAT_MPEG2:
		switch ((f[gobuf->frame_offset + 5] >> 3) & 0x7) {
		case 1:
			return V4L2_BUF_FLAG_KEYFRAME;
		case 2:
			return V4L2_BUF_FLAG_PFRAME;
		case 3:
			return V4L2_BUF_FLAG_BFRAME;
		default:
			return 0;
		}
	}

	return 0;
}