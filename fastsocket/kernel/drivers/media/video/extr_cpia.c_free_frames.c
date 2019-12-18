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
struct cpia_frame {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int FRAME_NUM ; 
 int /*<<< orphan*/  FRAME_UNUSED ; 

__attribute__((used)) static inline void free_frames(struct cpia_frame frame[FRAME_NUM])
{
	int i;

	for (i=0; i < FRAME_NUM; i++)
		frame[i].state = FRAME_UNUSED;
	return;
}