#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  key_free_fn ;
typedef  scalar_t__ key_equality_fn ;
struct TYPE_4__ {size_t num_bucket; int /*<<< orphan*/ * bucket; scalar_t__ keys_are_equal; int /*<<< orphan*/  data_fn; int /*<<< orphan*/  key_fn; int /*<<< orphan*/ * hash_fn; } ;
typedef  TYPE_1__ hash_map_t ;
typedef  int /*<<< orphan*/  hash_map_bucket_t ;
typedef  int /*<<< orphan*/ * hash_index_fn ;
typedef  int /*<<< orphan*/  data_free_fn ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ default_key_equality ; 
 void* osi_calloc (int) ; 
 int /*<<< orphan*/  osi_free (TYPE_1__*) ; 

hash_map_t *hash_map_new_internal(
    size_t num_bucket,
    hash_index_fn hash_fn,
    key_free_fn key_fn,
    data_free_fn data_fn,
    key_equality_fn equality_fn)
{
    assert(hash_fn != NULL);
    assert(num_bucket > 0);
    hash_map_t *hash_map = osi_calloc(sizeof(hash_map_t));
    if (hash_map == NULL) {
        return NULL;
    }

    hash_map->hash_fn = hash_fn;
    hash_map->key_fn = key_fn;
    hash_map->data_fn = data_fn;
    hash_map->keys_are_equal = equality_fn ? equality_fn : default_key_equality;

    hash_map->num_bucket = num_bucket;
    hash_map->bucket = osi_calloc(sizeof(hash_map_bucket_t) * num_bucket);
    if (hash_map->bucket == NULL) {
        osi_free(hash_map);
        return NULL;
    }
    return hash_map;
}