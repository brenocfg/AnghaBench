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

__attribute__((used)) static sector_t chunk_to_sector(struct dm_exception_store *store,
				chunk_t chunk)
{
	return chunk << store->chunk_shift;
}