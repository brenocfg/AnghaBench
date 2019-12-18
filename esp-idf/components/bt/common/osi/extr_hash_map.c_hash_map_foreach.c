#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  list_node_t ;
struct TYPE_5__ {size_t num_bucket; TYPE_1__* bucket; } ;
typedef  TYPE_2__ hash_map_t ;
typedef  int /*<<< orphan*/  (* hash_map_iter_cb ) (int /*<<< orphan*/ *,void*) ;
typedef  int /*<<< orphan*/  hash_map_entry_t ;
typedef  size_t hash_index_t ;
struct TYPE_4__ {int /*<<< orphan*/ * list; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* list_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_next (int /*<<< orphan*/  const*) ; 
 scalar_t__ list_node (int /*<<< orphan*/  const*) ; 

void hash_map_foreach(hash_map_t *hash_map, hash_map_iter_cb callback, void *context)
{
    assert(hash_map != NULL);
    assert(callback != NULL);

    for (hash_index_t i = 0; i < hash_map->num_bucket; ++i) {
        if (hash_map->bucket[i].list == NULL) {
            continue;
        }
        for (const list_node_t *iter = list_begin(hash_map->bucket[i].list);
                iter != list_end(hash_map->bucket[i].list);
                iter = list_next(iter)) {
            hash_map_entry_t *hash_map_entry = (hash_map_entry_t *)list_node(iter);
            if (!callback(hash_map_entry, context)) {
                return;
            }
        }
    }
}