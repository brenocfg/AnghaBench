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
struct video_data {int field_count; int /*<<< orphan*/  front; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_copy (struct video_data*,int) ; 
 int /*<<< orphan*/  submit_frame (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void end_field(struct video_data *video)
{
	/* logs(video->front); */
	if (1 == video->field_count)
		submit_frame(video->front);
	else
		init_copy(video, 1);
}