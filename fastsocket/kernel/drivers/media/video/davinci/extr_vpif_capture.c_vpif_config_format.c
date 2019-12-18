#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  field; } ;
struct TYPE_10__ {TYPE_3__ pix; } ;
struct TYPE_11__ {int /*<<< orphan*/  type; TYPE_4__ fmt; } ;
struct common_obj {TYPE_5__ fmt; int /*<<< orphan*/  memory; } ;
struct TYPE_7__ {scalar_t__ if_type; } ;
struct TYPE_8__ {TYPE_1__ iface; } ;
struct channel_obj {size_t channel_id; TYPE_2__ vpifparams; struct common_obj* common; } ;
struct TYPE_12__ {scalar_t__* numbuffers; int /*<<< orphan*/ * channel_bufsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_FIELD_ANY ; 
 int /*<<< orphan*/  V4L2_MEMORY_MMAP ; 
 int /*<<< orphan*/  V4L2_MEMORY_USERPTR ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_SBGGR8 ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_YUV422P ; 
 scalar_t__ VPIF_IF_RAW_BAYER ; 
 size_t VPIF_VIDEO_INDEX ; 
 TYPE_6__ config_params ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  vpif_dbg (int,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void vpif_config_format(struct channel_obj *ch)
{
	struct common_obj *common = &ch->common[VPIF_VIDEO_INDEX];

	vpif_dbg(2, debug, "vpif_config_format\n");

	common->fmt.fmt.pix.field = V4L2_FIELD_ANY;
	if (config_params.numbuffers[ch->channel_id] == 0)
		common->memory = V4L2_MEMORY_USERPTR;
	else
		common->memory = V4L2_MEMORY_MMAP;

	common->fmt.fmt.pix.sizeimage
	    = config_params.channel_bufsize[ch->channel_id];

	if (ch->vpifparams.iface.if_type == VPIF_IF_RAW_BAYER)
		common->fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_SBGGR8;
	else
		common->fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUV422P;
	common->fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
}