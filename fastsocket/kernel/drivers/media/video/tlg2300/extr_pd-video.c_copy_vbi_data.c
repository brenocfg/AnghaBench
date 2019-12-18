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
struct vbi_data {int vbi_size; int copied; TYPE_1__* video; struct front_face* front; } ;
struct front_face {int /*<<< orphan*/  curr_frame; } ;
struct TYPE_2__ {scalar_t__ field_count; } ;

/* Variables and functions */
 scalar_t__ get_frame (struct front_face*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char*,unsigned int) ; 
 char* videobuf_to_vmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void copy_vbi_data(struct vbi_data *vbi,
				char *src, unsigned int count)
{
	struct front_face *front = vbi->front;

	if (front && get_frame(front, NULL)) {
		char *buf = videobuf_to_vmalloc(front->curr_frame);

		if (vbi->video->field_count)
			buf += (vbi->vbi_size / 2);
		memcpy(buf + vbi->copied, src, count);
	}
	vbi->copied += count;
}