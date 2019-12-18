#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  field; } ;
struct TYPE_6__ {TYPE_1__ pix; } ;
struct TYPE_7__ {int /*<<< orphan*/  type; TYPE_2__ fmt; } ;
struct common_obj {TYPE_3__ fmt; int /*<<< orphan*/  memory; } ;
struct channel_obj {size_t channel_id; struct common_obj* common; } ;
struct TYPE_8__ {scalar_t__* numbuffers; int /*<<< orphan*/ * channel_bufsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  V4L2_FIELD_ANY ; 
 int /*<<< orphan*/  V4L2_MEMORY_MMAP ; 
 int /*<<< orphan*/  V4L2_MEMORY_USERPTR ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_YUV422P ; 
 size_t VPIF_VIDEO_INDEX ; 
 TYPE_4__ config_params ; 

__attribute__((used)) static void vpif_config_format(struct channel_obj *ch)
{
	struct common_obj *common = &ch->common[VPIF_VIDEO_INDEX];

	common->fmt.fmt.pix.field = V4L2_FIELD_ANY;
	if (config_params.numbuffers[ch->channel_id] == 0)
		common->memory = V4L2_MEMORY_USERPTR;
	else
		common->memory = V4L2_MEMORY_MMAP;

	common->fmt.fmt.pix.sizeimage =
			config_params.channel_bufsize[ch->channel_id];
	common->fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUV422P;
	common->fmt.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
}