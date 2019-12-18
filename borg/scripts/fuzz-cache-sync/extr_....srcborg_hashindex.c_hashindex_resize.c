#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_9__ {int key_size; int /*<<< orphan*/  min_empty; int /*<<< orphan*/  upper_limit; int /*<<< orphan*/  lower_limit; scalar_t__ num_entries; scalar_t__ num_buckets; scalar_t__ num_empty; int /*<<< orphan*/  buckets; int /*<<< orphan*/  value_size; } ;
typedef  TYPE_1__ HashIndex ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  hashindex_free (TYPE_1__*) ; 
 int /*<<< orphan*/  hashindex_free_buckets (TYPE_1__*) ; 
 TYPE_1__* hashindex_init (int,int,int /*<<< orphan*/ ) ; 
 unsigned char* hashindex_next_key (TYPE_1__*,unsigned char*) ; 
 int /*<<< orphan*/  hashindex_set (TYPE_1__*,unsigned char*,unsigned char*) ; 

__attribute__((used)) static int
hashindex_resize(HashIndex *index, int capacity)
{
    HashIndex *new;
    unsigned char *key = NULL;
    int32_t key_size = index->key_size;

    if(!(new = hashindex_init(capacity, key_size, index->value_size))) {
        return 0;
    }
    while((key = hashindex_next_key(index, key))) {
        if(!hashindex_set(new, key, key + key_size)) {
            /* This can only happen if there's a bug in the code calculating capacity */
            hashindex_free(new);
            return 0;
        }
    }
    hashindex_free_buckets(index);
    index->buckets = new->buckets;
    index->num_buckets = new->num_buckets;
    index->num_empty = index->num_buckets - index->num_entries;
    index->lower_limit = new->lower_limit;
    index->upper_limit = new->upper_limit;
    index->min_empty = new->min_empty;
    free(new);
    return 1;
}