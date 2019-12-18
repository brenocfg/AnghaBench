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
struct pool {int /*<<< orphan*/  pool_md; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR_LIMIT (char*,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  PM_READ_ONLY ; 
 int /*<<< orphan*/  abort_transaction (struct pool*) ; 
 int /*<<< orphan*/  dm_device_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pool_mode (struct pool*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void metadata_operation_failed(struct pool *pool, const char *op, int r)
{
	DMERR_LIMIT("%s: metadata operation '%s' failed: error = %d",
		    dm_device_name(pool->pool_md), op, r);

	abort_transaction(pool);
	set_pool_mode(pool, PM_READ_ONLY);
}