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
struct video_data {scalar_t__ field_count; struct vbi_data* vbi; } ;
struct vbi_data {int vbi_size; int copied; scalar_t__ front; } ;

/* Variables and functions */
 int /*<<< orphan*/  copy_vbi_data (struct vbi_data*,char*,unsigned int) ; 
 int /*<<< orphan*/  copy_video_data (struct video_data*,char*,unsigned int) ; 
 int /*<<< orphan*/  submit_frame (scalar_t__) ; 

__attribute__((used)) static inline void copy_vbi_video_data(struct video_data *video,
				char *src, unsigned int count)
{
	struct vbi_data *vbi = video->vbi;
	unsigned int vbi_delta = (vbi->vbi_size / 2) - vbi->copied;

	if (vbi_delta >= count) {
		copy_vbi_data(vbi, src, count);
	} else {
		if (vbi_delta) {
			copy_vbi_data(vbi, src, vbi_delta);

			/* we receive the two fields of the VBI*/
			if (vbi->front && video->field_count)
				submit_frame(vbi->front);
		}
		copy_video_data(video, src + vbi_delta, count - vbi_delta);
	}
}