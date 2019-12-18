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
struct omap_mbox {int seq_snd; } ;
typedef  int mbox_msg_t ;

/* Variables and functions */
 int /*<<< orphan*/  enable_seq_bit ; 

__attribute__((used)) static inline void mbox_seq_toggle(struct omap_mbox *mbox, mbox_msg_t * msg)
{
	if (!enable_seq_bit)
		return;

	/* add seq_snd to msg */
	*msg = (*msg & 0x7fffffff) | mbox->seq_snd;
	/* flip seq_snd */
	mbox->seq_snd ^= 1 << 31;
}