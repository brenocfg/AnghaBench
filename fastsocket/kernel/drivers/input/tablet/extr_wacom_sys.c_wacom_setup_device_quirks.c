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
struct wacom_features {scalar_t__ device_type; int x_max; int y_max; scalar_t__ type; int /*<<< orphan*/  quirks; } ;

/* Variables and functions */
 scalar_t__ BTN_TOOL_FINGER ; 
 scalar_t__ TABLETPC ; 
 scalar_t__ TABLETPC2FG ; 
 int /*<<< orphan*/  WACOM_QUIRK_MULTI_INPUT ; 

void wacom_setup_device_quirks(struct wacom_features *features)
{
	/* touch device found but size is not defined. use default */
	if (features->device_type == BTN_TOOL_FINGER && !features->x_max) {
		features->x_max = 1023;
		features->y_max = 1023;
	}

	/* these device have multiple inputs */
	if (features->type == TABLETPC || features->type == TABLETPC2FG)
		features->quirks |= WACOM_QUIRK_MULTI_INPUT;
}