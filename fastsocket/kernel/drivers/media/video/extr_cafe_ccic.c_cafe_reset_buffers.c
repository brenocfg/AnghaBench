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
struct cafe_camera {int next_buf; int nbufs; scalar_t__ specframes; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cafe_reset_buffers(struct cafe_camera *cam)
{
	int i;

	cam->next_buf = -1;
	for (i = 0; i < cam->nbufs; i++)
		clear_bit(i, &cam->flags);
	cam->specframes = 0;
}