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
struct pwc_device {int vframes_dumped; scalar_t__ vframe_count; } ;

/* Variables and functions */
 scalar_t__ FRAME_LOWMARK ; 
 int /*<<< orphan*/  PWC_DEBUG_FLOW (char*,scalar_t__) ; 

__attribute__((used)) static void pwc_frame_dumped(struct pwc_device *pdev)
{
	pdev->vframes_dumped++;
	if (pdev->vframe_count < FRAME_LOWMARK)
		return;

	if (pdev->vframes_dumped < 20)
		PWC_DEBUG_FLOW("Dumping frame %d\n", pdev->vframe_count);
	else if (pdev->vframes_dumped == 20)
		PWC_DEBUG_FLOW("Dumping frame %d (last message)\n",
				pdev->vframe_count);
}