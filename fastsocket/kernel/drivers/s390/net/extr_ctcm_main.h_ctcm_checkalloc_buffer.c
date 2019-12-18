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
struct channel {int flags; int /*<<< orphan*/ * trans_skb; } ;

/* Variables and functions */
 int CHANNEL_FLAGS_BUFSIZE_CHANGED ; 
 int ctcm_ch_alloc_buffer (struct channel*) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ctcm_checkalloc_buffer(struct channel *ch)
{
	if (ch->trans_skb == NULL)
		return ctcm_ch_alloc_buffer(ch);
	if (ch->flags & CHANNEL_FLAGS_BUFSIZE_CHANGED) {
		dev_kfree_skb(ch->trans_skb);
		return ctcm_ch_alloc_buffer(ch);
	}
	return 0;
}