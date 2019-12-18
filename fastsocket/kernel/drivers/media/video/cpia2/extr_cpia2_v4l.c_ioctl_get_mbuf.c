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
struct video_mbuf {int size; int frames; int* offsets; } ;
struct camera_data {int frame_size; int num_frames; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct video_mbuf*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ioctl_get_mbuf(void *arg, struct camera_data *cam)
{
	struct video_mbuf *vm;
	int i;
	vm = arg;

	memset(vm, 0, sizeof(*vm));
	vm->size = cam->frame_size*cam->num_frames;
	vm->frames = cam->num_frames;
	for (i = 0; i < cam->num_frames; i++)
		vm->offsets[i] = cam->frame_size * i;

	return 0;
}