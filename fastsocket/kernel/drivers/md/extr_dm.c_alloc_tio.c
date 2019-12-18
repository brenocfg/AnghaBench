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
struct dm_target_io {int /*<<< orphan*/  info; struct dm_target* ti; int /*<<< orphan*/  io; } ;
struct dm_target {int dummy; } ;
struct clone_info {int /*<<< orphan*/  io; TYPE_1__* md; } ;
struct TYPE_2__ {int /*<<< orphan*/  tio_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 struct dm_target_io* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct dm_target_io *alloc_tio(struct clone_info *ci,
				      struct dm_target *ti)
{
	struct dm_target_io *tio = mempool_alloc(ci->md->tio_pool, GFP_NOIO);

	tio->io = ci->io;
	tio->ti = ti;
	memset(&tio->info, 0, sizeof(tio->info));

	return tio;
}