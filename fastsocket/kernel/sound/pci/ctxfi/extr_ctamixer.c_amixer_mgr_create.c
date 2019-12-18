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
struct amixer_mgr {int /*<<< orphan*/  put_amixer; int /*<<< orphan*/  get_amixer; int /*<<< orphan*/  mgr_lock; int /*<<< orphan*/  mgr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMIXER ; 
 int /*<<< orphan*/  AMIXER_RESOURCE_NUM ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  get_amixer_rsc ; 
 int /*<<< orphan*/  kfree (struct amixer_mgr*) ; 
 struct amixer_mgr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_amixer_rsc ; 
 int rsc_mgr_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int amixer_mgr_create(void *hw, struct amixer_mgr **ramixer_mgr)
{
	int err;
	struct amixer_mgr *amixer_mgr;

	*ramixer_mgr = NULL;
	amixer_mgr = kzalloc(sizeof(*amixer_mgr), GFP_KERNEL);
	if (!amixer_mgr)
		return -ENOMEM;

	err = rsc_mgr_init(&amixer_mgr->mgr, AMIXER, AMIXER_RESOURCE_NUM, hw);
	if (err)
		goto error;

	spin_lock_init(&amixer_mgr->mgr_lock);

	amixer_mgr->get_amixer = get_amixer_rsc;
	amixer_mgr->put_amixer = put_amixer_rsc;

	*ramixer_mgr = amixer_mgr;

	return 0;

error:
	kfree(amixer_mgr);
	return err;
}