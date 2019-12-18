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
struct sn9c102_device {int /*<<< orphan*/ * frame_current; scalar_t__ nbuffers; TYPE_1__* frame; } ;
struct TYPE_2__ {int /*<<< orphan*/  bufmem; } ;

/* Variables and functions */
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sn9c102_release_buffers(struct sn9c102_device* cam)
{
	if (cam->nbuffers) {
		vfree(cam->frame[0].bufmem);
		cam->nbuffers = 0;
	}
	cam->frame_current = NULL;
}