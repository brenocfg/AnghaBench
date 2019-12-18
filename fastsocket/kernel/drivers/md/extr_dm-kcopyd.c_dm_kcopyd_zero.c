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
struct dm_kcopyd_client {int dummy; } ;
struct dm_io_region {int dummy; } ;
typedef  int /*<<< orphan*/  dm_kcopyd_notify_fn ;

/* Variables and functions */
 int dm_kcopyd_copy (struct dm_kcopyd_client*,int /*<<< orphan*/ *,unsigned int,struct dm_io_region*,unsigned int,int /*<<< orphan*/ ,void*) ; 

int dm_kcopyd_zero(struct dm_kcopyd_client *kc,
		   unsigned num_dests, struct dm_io_region *dests,
		   unsigned flags, dm_kcopyd_notify_fn fn, void *context)
{
	return dm_kcopyd_copy(kc, NULL, num_dests, dests, flags, fn, context);
}