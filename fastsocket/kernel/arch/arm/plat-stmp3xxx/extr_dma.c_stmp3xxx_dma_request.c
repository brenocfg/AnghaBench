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
struct stmp3xxx_dma_user {char const* name; int /*<<< orphan*/  inuse; int /*<<< orphan*/ * pool; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ IS_USED (int) ; 
 int /*<<< orphan*/  IS_VALID_CHANNEL (int) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct stmp3xxx_dma_user* channels ; 
 int /*<<< orphan*/ * dma_pool_create (char const*,struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pool_alignment ; 
 int /*<<< orphan*/  pool_item_size ; 

int stmp3xxx_dma_request(int ch, struct device *dev, const char *name)
{
	struct stmp3xxx_dma_user *user;
	int err = 0;

	user = channels + ch;
	if (!IS_VALID_CHANNEL(ch)) {
		err = -ENODEV;
		goto out;
	}
	if (IS_USED(ch)) {
		err = -EBUSY;
		goto out;
	}
	/* Create a pool to allocate dma commands from */
	user->pool = dma_pool_create(name, dev, pool_item_size,
				     pool_alignment, PAGE_SIZE);
	if (user->pool == NULL) {
		err = -ENOMEM;
		goto out;
	}
	user->name = name;
	user->inuse++;
out:
	return err;
}