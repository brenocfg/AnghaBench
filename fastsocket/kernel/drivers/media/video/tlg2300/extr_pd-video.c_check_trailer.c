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
typedef  int u32 ;
struct TYPE_3__ {int sizeimage; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct video_data {int lines_size; int lines_copied; int prev_left; int field_count; TYPE_2__ context; struct vbi_data* vbi; } ;
struct vbi_data {int vbi_size; int copied; } ;

/* Variables and functions */
 int /*<<< orphan*/  copy_video_data (struct video_data*,char*,int) ; 
 int /*<<< orphan*/  end_field (struct video_data*) ; 
 int /*<<< orphan*/  init_copy (struct video_data*,int) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static void check_trailer(struct video_data *video, char *src, int count)
{
	struct vbi_data *vbi = video->vbi;
	int offset; /* trailer's offset */
	char *buf;

	offset = (video->context.pix.sizeimage / 2 + vbi->vbi_size / 2)
		- (vbi->copied + video->lines_size * video->lines_copied);
	if (video->prev_left)
		offset -= (video->lines_size - video->prev_left);

	if (offset > count || offset <= 0)
		goto short_package;

	buf = src + offset;

	/* trailer : (VFHS) + U32 + U32 + field_num */
	if (!strncmp(buf, "VFHS", 4)) {
		int field_num = *((u32 *)(buf + 12));

		if ((field_num & 1) ^ video->field_count) {
			init_copy(video, video->field_count);
			return;
		}
		copy_video_data(video, src, offset);
	}
short_package:
	end_field(video);
}