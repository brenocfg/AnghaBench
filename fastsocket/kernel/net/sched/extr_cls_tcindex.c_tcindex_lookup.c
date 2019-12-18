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
typedef  size_t u16 ;
struct tcindex_filter_result {int dummy; } ;
struct tcindex_filter {size_t key; struct tcindex_filter_result result; struct tcindex_filter* next; } ;
struct tcindex_data {size_t hash; struct tcindex_filter** h; struct tcindex_filter_result* perfect; } ;

/* Variables and functions */
 scalar_t__ tcindex_filter_is_set (struct tcindex_filter_result*) ; 

__attribute__((used)) static struct tcindex_filter_result *
tcindex_lookup(struct tcindex_data *p, u16 key)
{
	struct tcindex_filter *f;

	if (p->perfect)
		return tcindex_filter_is_set(p->perfect + key) ?
			p->perfect + key : NULL;
	else if (p->h) {
		for (f = p->h[key % p->hash]; f; f = f->next)
			if (f->key == key)
				return &f->result;
	}

	return NULL;
}