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

/* Variables and functions */
 int /*<<< orphan*/  enable_seq_bit ; 

__attribute__((used)) static inline void mbox_seq_init(struct omap_mbox *mbox)
{
	if (!enable_seq_bit)
		return;

	/* any value other than 0 and 1 << 31 */
	mbox->seq_rcv = 0xffffffff;
}