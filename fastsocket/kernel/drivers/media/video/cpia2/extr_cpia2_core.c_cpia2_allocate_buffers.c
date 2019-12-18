#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct framebuf {int dummy; } ;
struct camera_data {int num_frames; int frame_size; TYPE_1__* workbuff; TYPE_1__* curbuff; TYPE_1__* buffers; scalar_t__ frame_buffer; } ;
struct TYPE_6__ {int num; struct TYPE_6__* next; scalar_t__ max_length; scalar_t__ length; void* status; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ERR (char*) ; 
 void* FRAME_EMPTY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ rvmalloc (int) ; 

int cpia2_allocate_buffers(struct camera_data *cam)
{
	int i;

	if(!cam->buffers) {
		u32 size = cam->num_frames*sizeof(struct framebuf);
		cam->buffers = kmalloc(size, GFP_KERNEL);
		if(!cam->buffers) {
			ERR("couldn't kmalloc frame buffer structures\n");
			return -ENOMEM;
		}
	}

	if(!cam->frame_buffer) {
		cam->frame_buffer = rvmalloc(cam->frame_size*cam->num_frames);
		if (!cam->frame_buffer) {
			ERR("couldn't vmalloc frame buffer data area\n");
			kfree(cam->buffers);
			cam->buffers = NULL;
			return -ENOMEM;
		}
	}

	for(i=0; i<cam->num_frames-1; ++i) {
		cam->buffers[i].next = &cam->buffers[i+1];
		cam->buffers[i].data = cam->frame_buffer +i*cam->frame_size;
		cam->buffers[i].status = FRAME_EMPTY;
		cam->buffers[i].length = 0;
		cam->buffers[i].max_length = 0;
		cam->buffers[i].num = i;
	}
	cam->buffers[i].next = cam->buffers;
	cam->buffers[i].data = cam->frame_buffer +i*cam->frame_size;
	cam->buffers[i].status = FRAME_EMPTY;
	cam->buffers[i].length = 0;
	cam->buffers[i].max_length = 0;
	cam->buffers[i].num = i;
	cam->curbuff = cam->buffers;
	cam->workbuff = cam->curbuff->next;
	DBG("buffers=%p, curbuff=%p, workbuff=%p\n", cam->buffers, cam->curbuff,
	    cam->workbuff);
	return 0;
}