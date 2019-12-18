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
struct stmp3xxx_dma_descriptor {int /*<<< orphan*/ * next_descr; int /*<<< orphan*/ * virtual_buf_ptr; scalar_t__ handle; int /*<<< orphan*/ * command; } ;
struct TYPE_2__ {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  IS_USED (int) ; 
 int /*<<< orphan*/  IS_VALID_CHANNEL (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_1__* channels ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

int stmp3xxx_dma_free_command(int channel,
			      struct stmp3xxx_dma_descriptor *descriptor)
{
	int err = 0;

	if (!IS_VALID_CHANNEL(channel)) {
		err = -ENODEV;
		goto out;
	}
	if (!IS_USED(channel)) {
		err = -EBUSY;
		goto out;
	}

	/* Return the command memory to the pool */
	dma_pool_free(channels[channel].pool, descriptor->command,
		      descriptor->handle);

	/* Initialise descriptor so we're not tempted to use it */
	descriptor->command = NULL;
	descriptor->handle = 0;
	descriptor->virtual_buf_ptr = NULL;
	descriptor->next_descr = NULL;

	WARN_ON(err);
out:
	return err;
}