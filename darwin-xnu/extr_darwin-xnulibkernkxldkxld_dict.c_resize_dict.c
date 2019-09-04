#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_13__ {scalar_t__ state; int /*<<< orphan*/  value; int /*<<< orphan*/  key; } ;
struct TYPE_12__ {int nitems; } ;
struct TYPE_11__ {TYPE_2__ resize_buckets; TYPE_2__ buckets; int /*<<< orphan*/  resize_threshold; scalar_t__ num_entries; } ;
typedef  TYPE_1__ KXLDDict ;
typedef  TYPE_2__ KXLDArray ;
typedef  TYPE_3__ DictEntry ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  RESIZE_THRESHOLD (int) ; 
 scalar_t__ USED ; 
 int /*<<< orphan*/  check (TYPE_1__*) ; 
 int /*<<< orphan*/  finish ; 
 int /*<<< orphan*/  kxld_array_clear (TYPE_2__*) ; 
 TYPE_3__* kxld_array_get_item (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  kxld_array_init (TYPE_2__*,int,scalar_t__) ; 
 int /*<<< orphan*/  kxld_dict_insert (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  require_noerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static kern_return_t
resize_dict(KXLDDict *dict)
{
    kern_return_t rval = KERN_FAILURE;
    KXLDArray tmparray;
    DictEntry *entry = NULL;
    u_int nbuckets = (dict->buckets.nitems * 2 + 1);
    u_int i = 0;

    check(dict);

    /* Initialize a new set of buckets to hold more entries */
    rval = kxld_array_init(&dict->resize_buckets, sizeof(DictEntry), nbuckets);
    require_noerr(rval, finish);

    /* Swap the new buckets with the old buckets */
    tmparray = dict->buckets;
    dict->buckets = dict->resize_buckets;
    dict->resize_buckets = tmparray; 

    /* Reset dictionary parameters */
    dict->num_entries = 0;
    dict->resize_threshold = RESIZE_THRESHOLD(dict->buckets.nitems);

    /* Rehash all of the entries */
    for (i = 0; i < dict->resize_buckets.nitems; ++i) {
        entry = kxld_array_get_item(&dict->resize_buckets, i);
        if (entry->state == USED) {
            rval = kxld_dict_insert(dict, entry->key, entry->value);
            require_noerr(rval, finish);
        }
    }

    /* Clear the old buckets */
    kxld_array_clear(&dict->resize_buckets);

    rval = KERN_SUCCESS;
    
finish:
    return rval;
}