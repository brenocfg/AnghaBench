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
struct omap_mbox {int seq_rcv; } ;
typedef  int mbox_msg_t ;

/* Variables and functions */
 int /*<<< orphan*/  enable_seq_bit ; 

__attribute__((used)) static inline int mbox_seq_test(struct omap_mbox *mbox, mbox_msg_t msg)
{
	mbox_msg_t seq;

	if (!enable_seq_bit)
		return 0;

	seq = msg & (1 << 31);
	if (seq == mbox->seq_rcv)
		return -1;
	mbox->seq_rcv = seq;
	return 0;
}