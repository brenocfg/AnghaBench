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
typedef  int /*<<< orphan*/  uint32_t ;
struct block_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __lookup_origin (struct block_device*) ; 
 int /*<<< orphan*/  __minimum_chunk_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _origins_lock ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint32_t get_origin_minimum_chunksize(struct block_device *bdev)
{
	uint32_t min_chunksize;

	down_read(&_origins_lock);
	min_chunksize = __minimum_chunk_size(__lookup_origin(bdev));
	up_read(&_origins_lock);

	return min_chunksize;
}