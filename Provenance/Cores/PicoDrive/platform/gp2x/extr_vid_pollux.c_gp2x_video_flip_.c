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

/* Variables and functions */
 int /*<<< orphan*/  FB_BUF_COUNT ; 
 int /*<<< orphan*/  pollux_video_flip (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gp2x_video_flip_(void)
{
	pollux_video_flip(FB_BUF_COUNT);
}