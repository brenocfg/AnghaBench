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
struct b3dfg_dev {TYPE_1__* buffers; } ;
struct TYPE_2__ {struct TYPE_2__** frame; } ;

/* Variables and functions */
 int B3DFG_FRAMES_PER_BUFFER ; 
 int b3dfg_nbuf ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

__attribute__((used)) static void free_all_frame_buffers(struct b3dfg_dev *fgdev)
{
	int i, j;
	for (i = 0; i < b3dfg_nbuf; i++)
		for (j = 0; j < B3DFG_FRAMES_PER_BUFFER; j++)
			kfree(fgdev->buffers[i].frame[j]);
	kfree(fgdev->buffers);
}