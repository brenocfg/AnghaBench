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
struct cmb_data {int size; struct cmb_data* last_block; } ;
struct cmb {int dummy; } ;
struct ccw_device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int num_channels; int /*<<< orphan*/  lock; struct cmb* mem; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ __get_free_pages (int,int /*<<< orphan*/ ) ; 
 int alloc_cmb_single (struct ccw_device*,struct cmb_data*) ; 
 TYPE_1__ cmb_area ; 
 int /*<<< orphan*/  cmf_activate (struct cmb*,int) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int) ; 
 int /*<<< orphan*/  kfree (struct cmb_data*) ; 
 void* kzalloc (int,int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct cmb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int alloc_cmb(struct ccw_device *cdev)
{
	int ret;
	struct cmb *mem;
	ssize_t size;
	struct cmb_data *cmb_data;

	/* Allocate private cmb_data. */
	cmb_data = kzalloc(sizeof(struct cmb_data), GFP_KERNEL);
	if (!cmb_data)
		return -ENOMEM;

	cmb_data->last_block = kzalloc(sizeof(struct cmb), GFP_KERNEL);
	if (!cmb_data->last_block) {
		kfree(cmb_data);
		return -ENOMEM;
	}
	cmb_data->size = sizeof(struct cmb);
	spin_lock(&cmb_area.lock);

	if (!cmb_area.mem) {
		/* there is no user yet, so we need a new area */
		size = sizeof(struct cmb) * cmb_area.num_channels;
		WARN_ON(!list_empty(&cmb_area.list));

		spin_unlock(&cmb_area.lock);
		mem = (void*)__get_free_pages(GFP_KERNEL | GFP_DMA,
				 get_order(size));
		spin_lock(&cmb_area.lock);

		if (cmb_area.mem) {
			/* ok, another thread was faster */
			free_pages((unsigned long)mem, get_order(size));
		} else if (!mem) {
			/* no luck */
			ret = -ENOMEM;
			goto out;
		} else {
			/* everything ok */
			memset(mem, 0, size);
			cmb_area.mem = mem;
			cmf_activate(cmb_area.mem, 1);
		}
	}

	/* do the actual allocation */
	ret = alloc_cmb_single(cdev, cmb_data);
out:
	spin_unlock(&cmb_area.lock);
	if (ret) {
		kfree(cmb_data->last_block);
		kfree(cmb_data);
	}
	return ret;
}