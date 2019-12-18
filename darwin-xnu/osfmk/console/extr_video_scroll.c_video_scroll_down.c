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
 int /*<<< orphan*/  bcopy (void*,void*,int) ; 

void video_scroll_down(void * start, /* HIGH addr */
                       void * end,   /* LOW addr */
                       void * dest)  /* HIGH addr */
{
	bcopy(end, dest, ((char *)start - (char *)end) << 2);
}