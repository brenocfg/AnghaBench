#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  rh; } ;
struct raid_set {TYPE_2__ recover; int /*<<< orphan*/  sc; TYPE_1__* dev; int /*<<< orphan*/  ti; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_put_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_region_hash_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct raid_set*) ; 
 int /*<<< orphan*/  sc_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void context_free(struct raid_set *rs, unsigned p)
{
	while (p--)
		dm_put_device(rs->ti, rs->dev[p].dev);

	sc_exit(&rs->sc);
	dm_region_hash_destroy(rs->recover.rh); /* Destroys dirty log too. */
	kfree(rs);
}