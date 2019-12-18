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
typedef  size_t u32 ;
typedef  size_t u16 ;
struct hda_cache_rec {size_t* hash; int /*<<< orphan*/  buf; } ;
struct hda_cache_head {size_t key; size_t next; scalar_t__ dirty; scalar_t__ val; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (size_t*) ; 
 struct hda_cache_head* get_hash (struct hda_cache_rec*,size_t) ; 
 size_t snd_array_index (int /*<<< orphan*/ *,struct hda_cache_head*) ; 
 struct hda_cache_head* snd_array_new (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct hda_cache_head  *get_alloc_hash(struct hda_cache_rec *cache,
					      u32 key)
{
	struct hda_cache_head *info = get_hash(cache, key);
	if (!info) {
		u16 idx, cur;
		/* add a new hash entry */
		info = snd_array_new(&cache->buf);
		if (!info)
			return NULL;
		cur = snd_array_index(&cache->buf, info);
		info->key = key;
		info->val = 0;
		info->dirty = 0;
		idx = key % (u16)ARRAY_SIZE(cache->hash);
		info->next = cache->hash[idx];
		cache->hash[idx] = cur;
	}
	return info;
}