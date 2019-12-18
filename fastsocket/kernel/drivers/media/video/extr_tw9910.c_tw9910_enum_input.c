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
struct v4l2_input {int /*<<< orphan*/  name; int /*<<< orphan*/  std; int /*<<< orphan*/  type; } ;
struct soc_camera_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_INPUT_TYPE_TUNER ; 
 int /*<<< orphan*/  V4L2_STD_UNKNOWN ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int tw9910_enum_input(struct soc_camera_device *icd,
			     struct v4l2_input *inp)
{
	inp->type = V4L2_INPUT_TYPE_TUNER;
	inp->std  = V4L2_STD_UNKNOWN;
	strcpy(inp->name, "Video");

	return 0;
}