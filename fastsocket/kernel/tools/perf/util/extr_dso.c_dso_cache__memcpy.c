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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
struct dso_cache {scalar_t__ data; scalar_t__ size; scalar_t__ offset; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

__attribute__((used)) static ssize_t
dso_cache__memcpy(struct dso_cache *cache, u64 offset,
		  u8 *data, u64 size)
{
	u64 cache_offset = offset - cache->offset;
	u64 cache_size   = min(cache->size - cache_offset, size);

	memcpy(data, cache->data + cache_offset, cache_size);
	return cache_size;
}