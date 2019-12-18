#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * buf; } ;
struct TYPE_8__ {int key_size; int value_size; int num_buckets; int num_empty; int bucket_size; TYPE_1__ buckets_buffer; int /*<<< orphan*/  min_empty; int /*<<< orphan*/  upper_limit; int /*<<< orphan*/  lower_limit; scalar_t__ num_entries; int /*<<< orphan*/  buckets; } ;
typedef  TYPE_2__ HashIndex ;

/* Variables and functions */
 int /*<<< orphan*/  BUCKET_MARK_EMPTY (TYPE_2__*,int) ; 
 int /*<<< orphan*/  EPRINTF (char*) ; 
 int /*<<< orphan*/  calloc (int,int) ; 
 int fit_size (int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  get_lower_limit (int) ; 
 int /*<<< orphan*/  get_min_empty (int) ; 
 int /*<<< orphan*/  get_upper_limit (int) ; 
 TYPE_2__* malloc (int) ; 

__attribute__((used)) static HashIndex *
hashindex_init(int capacity, int key_size, int value_size)
{
    HashIndex *index;
    int i;
    capacity = fit_size(capacity);

    if(!(index = malloc(sizeof(HashIndex)))) {
        EPRINTF("malloc header failed");
        return NULL;
    }
    if(!(index->buckets = calloc(capacity, key_size + value_size))) {
        EPRINTF("malloc buckets failed");
        free(index);
        return NULL;
    }
    index->num_entries = 0;
    index->key_size = key_size;
    index->value_size = value_size;
    index->num_buckets = capacity;
    index->num_empty = capacity;
    index->bucket_size = index->key_size + index->value_size;
    index->lower_limit = get_lower_limit(index->num_buckets);
    index->upper_limit = get_upper_limit(index->num_buckets);
    index->min_empty = get_min_empty(index->num_buckets);
#ifndef BORG_NO_PYTHON
    index->buckets_buffer.buf = NULL;
#endif
    for(i = 0; i < capacity; i++) {
        BUCKET_MARK_EMPTY(index, i);
    }
    return index;
}