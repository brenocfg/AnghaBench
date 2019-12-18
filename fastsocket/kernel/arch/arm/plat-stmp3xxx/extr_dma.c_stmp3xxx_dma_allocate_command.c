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
struct stmp3xxx_dma_user {int /*<<< orphan*/  pool; } ;
struct stmp3xxx_dma_descriptor {int /*<<< orphan*/  command; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_USED (int) ; 
 int /*<<< orphan*/  IS_VALID_CHANNEL (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct stmp3xxx_dma_user* channels ; 
 int /*<<< orphan*/  dma_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pool_item_size ; 

int stmp3xxx_dma_allocate_command(int channel,
				  struct stmp3xxx_dma_descriptor *descriptor)
{
	struct stmp3xxx_dma_user *user = channels + channel;
	int err = 0;

	if (!IS_VALID_CHANNEL(channel)) {
		err = -ENODEV;
		goto out;
	}
	if (!IS_USED(channel)) {
		err = -EBUSY;
		goto out;
	}
	if (descriptor == NULL) {
		err = -EINVAL;
		goto out;
	}

	/* Allocate memory for a command from the buffer */
	descriptor->command =
	    dma_pool_alloc(user->pool, GFP_KERNEL, &descriptor->handle);

	/* Check it worked */
	if (!descriptor->command) {
		err = -ENOMEM;
		goto out;
	}

	memset(descriptor->command, 0, pool_item_size);
out:
	WARN_ON(err);
	return err;
}