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
struct m2p_channel {int /*<<< orphan*/ * client; int /*<<< orphan*/  lock; int /*<<< orphan*/  clk; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init_channel(struct m2p_channel *ch)
{
	ch->clk = clk_get(NULL, ch->name);
	if (IS_ERR(ch->clk))
		return PTR_ERR(ch->clk);

	spin_lock_init(&ch->lock);
	ch->client = NULL;

	return 0;
}