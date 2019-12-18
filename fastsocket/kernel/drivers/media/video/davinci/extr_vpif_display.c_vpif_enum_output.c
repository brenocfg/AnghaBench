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
struct vpif_display_config {size_t output_count; int /*<<< orphan*/ * output; } ;
struct v4l2_output {size_t index; int /*<<< orphan*/  std; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct file {int dummy; } ;
struct TYPE_2__ {struct vpif_display_config* platform_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM646X_V4L2_STD ; 
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_OUTPUT_TYPE_ANALOG ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpif_dbg (int,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* vpif_dev ; 

__attribute__((used)) static int vpif_enum_output(struct file *file, void *fh,
				struct v4l2_output *output)
{

	struct vpif_display_config *config = vpif_dev->platform_data;

	if (output->index >= config->output_count) {
		vpif_dbg(1, debug, "Invalid output index\n");
		return -EINVAL;
	}

	strcpy(output->name, config->output[output->index]);
	output->type = V4L2_OUTPUT_TYPE_ANALOG;
	output->std = DM646X_V4L2_STD;

	return 0;
}