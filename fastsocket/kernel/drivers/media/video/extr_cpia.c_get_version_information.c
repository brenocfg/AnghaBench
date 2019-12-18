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
struct cam_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPIA_COMMAND_GetCPIAVersion ; 
 int /*<<< orphan*/  CPIA_COMMAND_GetPnPID ; 
 int /*<<< orphan*/  do_command (struct cam_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_version_information(struct cam_data *cam)
{
	/* GetCPIAVersion */
	do_command(cam, CPIA_COMMAND_GetCPIAVersion, 0, 0, 0, 0);

	/* GetPnPID */
	do_command(cam, CPIA_COMMAND_GetPnPID, 0, 0, 0, 0);
}