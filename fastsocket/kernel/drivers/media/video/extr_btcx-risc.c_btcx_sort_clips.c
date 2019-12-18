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
struct TYPE_2__ {scalar_t__ left; } ;
struct v4l2_clip {TYPE_1__ c; } ;

/* Variables and functions */

void
btcx_sort_clips(struct v4l2_clip *clips, unsigned int nclips)
{
	struct v4l2_clip swap;
	int i,j,n;

	if (nclips < 2)
		return;
	for (i = nclips-2; i >= 0; i--) {
		for (n = 0, j = 0; j <= i; j++) {
			if (clips[j].c.left > clips[j+1].c.left) {
				swap = clips[j];
				clips[j] = clips[j+1];
				clips[j+1] = swap;
				n++;
			}
		}
		if (0 == n)
			break;
	}
}