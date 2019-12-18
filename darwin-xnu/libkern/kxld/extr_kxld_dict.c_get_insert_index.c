#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_9__ {int nitems; } ;
struct TYPE_8__ {scalar_t__ state; int /*<<< orphan*/  key; } ;
struct TYPE_7__ {int (* hash ) (TYPE_1__ const*,void const*) ;TYPE_5__ buckets; int /*<<< orphan*/  (* cmp ) (int /*<<< orphan*/ ,void const*) ;} ;
typedef  TYPE_1__ KXLDDict ;
typedef  TYPE_2__ DictEntry ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ USED ; 
 int /*<<< orphan*/  finish ; 
 TYPE_2__* kxld_array_get_item (TYPE_5__*,int) ; 
 int /*<<< orphan*/  require_action (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_1__ const*,void const*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,void const*) ; 

__attribute__((used)) static kern_return_t
get_insert_index(const KXLDDict *dict, const void *key, u_int *r_index)
{
    kern_return_t rval = KERN_FAILURE;
    DictEntry *entry = NULL;
    u_int base, idx;

    base = idx = dict->hash(dict, key);
    
    /* Iterate through the buckets until we find an EMPTY bucket, a DELETED
     * bucket, or a key match.
     */
    entry = kxld_array_get_item(&dict->buckets, idx);
    while (entry->state == USED && !dict->cmp(entry->key, key)) {
        idx = (idx + 1) % dict->buckets.nitems;
        require_action(base != idx, finish, rval=KERN_FAILURE);
        entry = kxld_array_get_item(&dict->buckets, idx);
    }
    
    *r_index = idx;
    rval = KERN_SUCCESS;
    
finish:
    return rval;
}