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
struct TYPE_4__ {int /*<<< orphan*/  (* data_fn ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* key_fn ) (void*) ;} ;
typedef  TYPE_1__ hash_map_t ;
struct TYPE_5__ {int /*<<< orphan*/  data; scalar_t__ key; TYPE_1__* hash_map; } ;
typedef  TYPE_2__ hash_map_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (void*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bucket_free_(void *data)
{
    assert(data != NULL);
    hash_map_entry_t *hash_map_entry = (hash_map_entry_t *)data;
    const hash_map_t *hash_map = hash_map_entry->hash_map;

    if (hash_map->key_fn) {
        hash_map->key_fn((void *)hash_map_entry->key);
    }
    if (hash_map->data_fn) {
        hash_map->data_fn(hash_map_entry->data);
    }
    osi_free(hash_map_entry);
}