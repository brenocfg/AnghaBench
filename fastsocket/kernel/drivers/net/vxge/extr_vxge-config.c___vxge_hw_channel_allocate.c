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
typedef  int u32 ;
struct __vxge_hw_vpath_handle {TYPE_1__* vpath; } ;
struct __vxge_hw_ring {int dummy; } ;
struct __vxge_hw_fifo {int dummy; } ;
struct __vxge_hw_device {int /*<<< orphan*/  first_vp_id; int /*<<< orphan*/  common_reg; } ;
struct __vxge_hw_channel {int type; int per_dtr_space; int length; int vp_id; int free_ptr; int reserve_ptr; int /*<<< orphan*/ * orig_arr; scalar_t__ reserve_top; int /*<<< orphan*/ * reserve_arr; int /*<<< orphan*/ * free_arr; int /*<<< orphan*/ * work_arr; void* userdata; struct __vxge_hw_vpath_handle* vph; struct __vxge_hw_device* devh; int /*<<< orphan*/  first_vp_id; int /*<<< orphan*/  common_reg; int /*<<< orphan*/  item; } ;
typedef  enum __vxge_hw_channel_type { ____Placeholder___vxge_hw_channel_type } __vxge_hw_channel_type ;
struct TYPE_2__ {int vp_id; struct __vxge_hw_device* hldev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
#define  VXGE_HW_CHANNEL_TYPE_FIFO 129 
#define  VXGE_HW_CHANNEL_TYPE_RING 128 
 int /*<<< orphan*/  __vxge_hw_channel_free (struct __vxge_hw_channel*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

struct __vxge_hw_channel*
__vxge_hw_channel_allocate(struct __vxge_hw_vpath_handle *vph,
			   enum __vxge_hw_channel_type type,
	u32 length, u32 per_dtr_space, void *userdata)
{
	struct __vxge_hw_channel *channel;
	struct __vxge_hw_device *hldev;
	int size = 0;
	u32 vp_id;

	hldev = vph->vpath->hldev;
	vp_id = vph->vpath->vp_id;

	switch (type) {
	case VXGE_HW_CHANNEL_TYPE_FIFO:
		size = sizeof(struct __vxge_hw_fifo);
		break;
	case VXGE_HW_CHANNEL_TYPE_RING:
		size = sizeof(struct __vxge_hw_ring);
		break;
	default:
		break;
	}

	channel = kzalloc(size, GFP_KERNEL);
	if (channel == NULL)
		goto exit0;
	INIT_LIST_HEAD(&channel->item);

	channel->common_reg = hldev->common_reg;
	channel->first_vp_id = hldev->first_vp_id;
	channel->type = type;
	channel->devh = hldev;
	channel->vph = vph;
	channel->userdata = userdata;
	channel->per_dtr_space = per_dtr_space;
	channel->length = length;
	channel->vp_id = vp_id;

	channel->work_arr = kzalloc(sizeof(void *)*length, GFP_KERNEL);
	if (channel->work_arr == NULL)
		goto exit1;

	channel->free_arr = kzalloc(sizeof(void *)*length, GFP_KERNEL);
	if (channel->free_arr == NULL)
		goto exit1;
	channel->free_ptr = length;

	channel->reserve_arr = kzalloc(sizeof(void *)*length, GFP_KERNEL);
	if (channel->reserve_arr == NULL)
		goto exit1;
	channel->reserve_ptr = length;
	channel->reserve_top = 0;

	channel->orig_arr = kzalloc(sizeof(void *)*length, GFP_KERNEL);
	if (channel->orig_arr == NULL)
		goto exit1;

	return channel;
exit1:
	__vxge_hw_channel_free(channel);

exit0:
	return NULL;
}