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
struct vpif_subdev_info {int /*<<< orphan*/  name; } ;
struct vpif_capture_config {int subdev_count; struct vpif_subdev_info* subdev_info; struct vpif_capture_chan_config* chan_config; } ;
struct vpif_capture_chan_config {int input_count; TYPE_1__* inputs; } ;
struct channel_obj {size_t channel_id; } ;
struct TYPE_4__ {int /*<<< orphan*/ ** sd; } ;
struct TYPE_3__ {char* subdev_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  vpif_dbg (int,int /*<<< orphan*/ ,char*) ; 
 TYPE_2__ vpif_obj ; 

__attribute__((used)) static struct vpif_subdev_info *vpif_map_sub_device_to_input(
				struct channel_obj *ch,
				struct vpif_capture_config *vpif_cfg,
				int input_index,
				int *sub_device_index)
{
	struct vpif_capture_chan_config *chan_cfg;
	struct vpif_subdev_info *subdev_info = NULL;
	const char *subdev_name = NULL;
	int i;

	vpif_dbg(2, debug, "vpif_map_sub_device_to_input\n");

	chan_cfg = &vpif_cfg->chan_config[ch->channel_id];

	/**
	 * search through the inputs to find the sub device supporting
	 * the input
	 */
	for (i = 0; i < chan_cfg->input_count; i++) {
		/* For each sub device, loop through input */
		if (i == input_index) {
			subdev_name = chan_cfg->inputs[i].subdev_name;
			break;
		}
	}

	/* if reached maximum. return null */
	if (i == chan_cfg->input_count || (NULL == subdev_name))
		return subdev_info;

	/* loop through the sub device list to get the sub device info */
	for (i = 0; i < vpif_cfg->subdev_count; i++) {
		subdev_info = &vpif_cfg->subdev_info[i];
		if (!strcmp(subdev_info->name, subdev_name))
			break;
	}

	if (i == vpif_cfg->subdev_count)
		return subdev_info;

	/* check if the sub device is registered */
	if (NULL == vpif_obj.sd[i])
		return NULL;

	*sub_device_index = i;
	return subdev_info;
}