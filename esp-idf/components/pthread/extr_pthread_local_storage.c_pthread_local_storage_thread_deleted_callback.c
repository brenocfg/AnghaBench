#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  value; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ values_list_t ;
typedef  TYPE_1__ value_entry_t ;
struct TYPE_11__ {int /*<<< orphan*/  (* destructor ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ key_entry_t ;

/* Variables and functions */
 TYPE_1__* SLIST_FIRST (TYPE_1__*) ; 
 TYPE_1__* SLIST_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_3__* find_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pthread_local_storage_thread_deleted_callback(int index, void *v_tls)
{
    values_list_t *tls = (values_list_t *)v_tls;
    assert(tls != NULL);

    /* Walk the list, freeing all entries and calling destructors if they are registered */
    value_entry_t *entry = SLIST_FIRST(tls);
    while(entry != NULL) {
        // This is a little slow, walking the linked list of keys once per value,
        // but assumes that the thread's value list will have less entries
        // than the keys list
        key_entry_t *key = find_key(entry->key);
        if (key != NULL && key->destructor != NULL) {
            key->destructor(entry->value);
        }
        value_entry_t *next_entry = SLIST_NEXT(entry, next);
        free(entry);
        entry = next_entry;
    }
    free(tls);
}