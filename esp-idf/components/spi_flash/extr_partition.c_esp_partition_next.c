#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ type; scalar_t__ subtype; int /*<<< orphan*/  label; } ;
typedef  TYPE_1__ esp_partition_t ;
typedef  TYPE_2__* esp_partition_iterator_t ;
struct TYPE_10__ {TYPE_1__ info; } ;
struct TYPE_9__ {scalar_t__ type; int subtype; TYPE_7__* next_item; TYPE_1__* info; int /*<<< orphan*/ * label; } ;

/* Variables and functions */
 void* SLIST_NEXT (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _lock_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _lock_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  esp_partition_iterator_release (TYPE_2__*) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  s_partition_list_lock ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

esp_partition_iterator_t esp_partition_next(esp_partition_iterator_t it)
{
    assert(it);
    // iterator reached the end of linked list?
    if (it->next_item == NULL) {
        esp_partition_iterator_release(it);
        return NULL;
    }
    _lock_acquire(&s_partition_list_lock);
    for (; it->next_item != NULL; it->next_item = SLIST_NEXT(it->next_item, next)) {
        esp_partition_t* p = &it->next_item->info;
        if (it->type != p->type) {
            continue;
        }
        if (it->subtype != 0xff && it->subtype != p->subtype) {
            continue;
        }
        if (it->label != NULL && strcmp(it->label, p->label) != 0) {
            continue;
        }
        // all constraints match, bail out
        break;
    }
    _lock_release(&s_partition_list_lock);
    if (it->next_item == NULL) {
        esp_partition_iterator_release(it);
        return NULL;
    }
    it->info = &it->next_item->info;
    it->next_item = SLIST_NEXT(it->next_item, next);
    return it;
}