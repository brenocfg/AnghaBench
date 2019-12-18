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
struct hash_bucket {int dummy; } ;
struct dma_debug_entry {int dummy; } ;

/* Variables and functions */
 struct dma_debug_entry* __hash_bucket_find (struct hash_bucket*,struct dma_debug_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exact_match ; 

__attribute__((used)) static struct dma_debug_entry *bucket_find_exact(struct hash_bucket *bucket,
						 struct dma_debug_entry *ref)
{
	return __hash_bucket_find(bucket, ref, exact_match);
}