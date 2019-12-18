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
struct stmp3xxx_dma_user {int /*<<< orphan*/  inuse; int /*<<< orphan*/ * pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  IS_USED (int) ; 
 int /*<<< orphan*/  IS_VALID_CHANNEL (int) ; 
 struct stmp3xxx_dma_user* channels ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ *) ; 

int stmp3xxx_dma_release(int ch)
{
	struct stmp3xxx_dma_user *user = channels + ch;
	int err = 0;

	if (!IS_VALID_CHANNEL(ch)) {
		err = -ENODEV;
		goto out;
	}
	if (!IS_USED(ch)) {
		err = -EBUSY;
		goto out;
	}
	BUG_ON(user->pool == NULL);
	dma_pool_destroy(user->pool);
	user->inuse--;
out:
	return err;
}