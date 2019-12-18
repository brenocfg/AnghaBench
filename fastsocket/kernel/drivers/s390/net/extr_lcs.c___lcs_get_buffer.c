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
struct lcs_channel {int io_idx; struct lcs_buffer* iob; } ;
struct lcs_buffer {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ LCS_BUF_STATE_EMPTY ; 
 scalar_t__ LCS_BUF_STATE_LOCKED ; 
 int /*<<< orphan*/  LCS_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int LCS_NUM_BUFFS ; 
 int /*<<< orphan*/  trace ; 

__attribute__((used)) static struct lcs_buffer *
__lcs_get_buffer(struct lcs_channel *channel)
{
	int index;

	LCS_DBF_TEXT(5, trace, "_getbuff");
	index = channel->io_idx;
	do {
		if (channel->iob[index].state == LCS_BUF_STATE_EMPTY) {
			channel->iob[index].state = LCS_BUF_STATE_LOCKED;
			return channel->iob + index;
		}
		index = (index + 1) & (LCS_NUM_BUFFS - 1);
	} while (index != channel->io_idx);
	return NULL;
}