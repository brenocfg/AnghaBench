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
struct v4l2_querymenu {int id; size_t index; scalar_t__ name; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (char const**) ; 
 int EINVAL ; 
#define  V4L2_CID_POWER_LINE_FREQUENCY 128 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 

__attribute__((used)) static int sd_querymenu(struct gspca_dev *gspca_dev,
			struct v4l2_querymenu *menu)
{
	static const char *freq_nm[3] = {"NoFliker", "50 Hz", "60 Hz"};

	switch (menu->id) {
	case V4L2_CID_POWER_LINE_FREQUENCY:
		if (menu->index >= ARRAY_SIZE(freq_nm))
			break;
		strcpy((char *) menu->name, freq_nm[menu->index]);
		return 0;
	}
	return -EINVAL;
}