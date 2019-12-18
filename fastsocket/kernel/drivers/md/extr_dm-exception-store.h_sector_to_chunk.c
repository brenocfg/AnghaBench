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
struct dm_exception_store {int chunk_shift; } ;
typedef  int sector_t ;
typedef  int chunk_t ;

/* Variables and functions */

__attribute__((used)) static inline chunk_t sector_to_chunk(struct dm_exception_store *store,
				      sector_t sector)
{
	return sector >> store->chunk_shift;
}