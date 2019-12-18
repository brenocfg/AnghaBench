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
struct TYPE_2__ {int /*<<< orphan*/  streamStartLine; } ;
struct cam_data {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPIA_COMMAND_InitStreamCap ; 
 int do_command (struct cam_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int init_stream_cap(struct cam_data *cam)
{
	return do_command(cam, CPIA_COMMAND_InitStreamCap,
			  0, cam->params.streamStartLine, 0, 0);
}