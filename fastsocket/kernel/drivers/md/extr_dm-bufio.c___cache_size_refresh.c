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

/* Variables and functions */
 int ACCESS_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dm_bufio_cache_size ; 
 int dm_bufio_cache_size_latch ; 
 int dm_bufio_cache_size_per_client ; 
 scalar_t__ dm_bufio_client_count ; 
 int /*<<< orphan*/  dm_bufio_clients_lock ; 
 int dm_bufio_default_cache_size ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __cache_size_refresh(void)
{
	BUG_ON(!mutex_is_locked(&dm_bufio_clients_lock));
	BUG_ON(dm_bufio_client_count < 0);

	dm_bufio_cache_size_latch = ACCESS_ONCE(dm_bufio_cache_size);

	/*
	 * Use default if set to 0 and report the actual cache size used.
	 */
	if (!dm_bufio_cache_size_latch) {
		(void)cmpxchg(&dm_bufio_cache_size, 0,
			      dm_bufio_default_cache_size);
		dm_bufio_cache_size_latch = dm_bufio_default_cache_size;
	}

	dm_bufio_cache_size_per_client = dm_bufio_cache_size_latch /
					 (dm_bufio_client_count ? : 1);
}