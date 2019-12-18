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
 struct hash_bucket* get_hash_bucket (struct dma_debug_entry*,unsigned long*) ; 
 int /*<<< orphan*/  hash_bucket_add (struct hash_bucket*,struct dma_debug_entry*) ; 
 int /*<<< orphan*/  put_hash_bucket (struct hash_bucket*,unsigned long*) ; 

__attribute__((used)) static void add_dma_entry(struct dma_debug_entry *entry)
{
	struct hash_bucket *bucket;
	unsigned long flags;

	bucket = get_hash_bucket(entry, &flags);
	hash_bucket_add(bucket, entry);
	put_hash_bucket(bucket, &flags);
}