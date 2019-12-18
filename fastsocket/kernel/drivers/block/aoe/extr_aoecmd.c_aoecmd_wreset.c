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
struct aoetgt {int maxout; int ssthresh; int nframes; int next_cwnd; } ;

/* Variables and functions */

void
aoecmd_wreset(struct aoetgt *t)
{
	t->maxout = 1;
	t->ssthresh = t->nframes / 2;
	t->next_cwnd = t->nframes;
}