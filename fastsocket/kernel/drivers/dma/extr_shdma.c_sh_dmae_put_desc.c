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
struct sh_dmae_chan {int /*<<< orphan*/  desc_lock; int /*<<< orphan*/  ld_free; } ;
struct sh_desc {int /*<<< orphan*/  node; int /*<<< orphan*/  tx_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sh_dmae_put_desc(struct sh_dmae_chan *sh_chan, struct sh_desc *desc)
{
	if (desc) {
		spin_lock_bh(&sh_chan->desc_lock);

		list_splice_init(&desc->tx_list, &sh_chan->ld_free);
		list_add(&desc->node, &sh_chan->ld_free);

		spin_unlock_bh(&sh_chan->desc_lock);
	}
}