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
struct lcs_channel {TYPE_1__* ccws; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int CCW_FLAG_PCI ; 
 int CCW_FLAG_SUSPEND ; 
 int /*<<< orphan*/  LCS_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int LCS_NUM_BUFFS ; 
 int /*<<< orphan*/  trace ; 

__attribute__((used)) static inline void
__lcs_ready_buffer_bits(struct lcs_channel *channel, int index)
{
	int prev, next;

	LCS_DBF_TEXT(5, trace, "rdybits");
	prev = (index - 1) & (LCS_NUM_BUFFS - 1);
	next = (index + 1) & (LCS_NUM_BUFFS - 1);
	/* Check if we may clear the suspend bit of this buffer. */
	if (channel->ccws[next].flags & CCW_FLAG_SUSPEND) {
		/* Check if we have to set the PCI bit. */
		if (!(channel->ccws[prev].flags & CCW_FLAG_SUSPEND))
			/* Suspend bit of the previous buffer is not set. */
			channel->ccws[index].flags |= CCW_FLAG_PCI;
		/* Suspend bit of the next buffer is set. */
		channel->ccws[index].flags &= ~CCW_FLAG_SUSPEND;
	}
}