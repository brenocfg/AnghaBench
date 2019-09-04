#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * d86_seg_prefix; } ;
typedef  TYPE_1__ dis86_t ;

/* Variables and functions */

__attribute__((used)) static void
dtrace_check_override(dis86_t *x, int opindex)
{
#ifdef DIS_TEXT
	if (x->d86_seg_prefix) {
		(void) strlcat(x->d86_opnd[opindex].d86_prefix,
		    x->d86_seg_prefix, PFIXLEN);
	}
#else
	#pragma unused (opindex)
#endif
	x->d86_seg_prefix = NULL;
}