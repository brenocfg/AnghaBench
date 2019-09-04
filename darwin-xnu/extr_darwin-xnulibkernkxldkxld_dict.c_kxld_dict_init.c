#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  TYPE_1__* kxld_dict_hash ;
typedef  TYPE_1__* kxld_dict_cmp ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_8__ {int /*<<< orphan*/  resize_threshold; scalar_t__ num_entries; struct TYPE_8__* cmp; struct TYPE_8__* hash; int /*<<< orphan*/  buckets; } ;
typedef  TYPE_1__ KXLDDict ;
typedef  int /*<<< orphan*/  DictEntry ;

/* Variables and functions */
 int DEFAULT_DICT_SIZE ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int MIN_BUCKETS (int) ; 
 int /*<<< orphan*/  RESIZE_THRESHOLD (int) ; 
 int /*<<< orphan*/  check (TYPE_1__*) ; 
 int /*<<< orphan*/  finish ; 
 int /*<<< orphan*/  kxld_array_init (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  require_noerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
kxld_dict_init(KXLDDict * dict, kxld_dict_hash hash, kxld_dict_cmp cmp, 
    u_int num_entries) 
{
    kern_return_t rval = KERN_FAILURE;
    u_int min_buckets = MIN_BUCKETS(num_entries);
    u_int num_buckets = DEFAULT_DICT_SIZE;
    
    check(dict);
    check(hash);
    check(cmp);
    
    /* We want the number of allocated buckets to be at least twice that of the 
     * number to be inserted.
     */
    while (min_buckets > num_buckets) {
        num_buckets *= 2;
        num_buckets++;
    }
    
    /* Allocate enough buckets for the anticipated number of entries */
    rval = kxld_array_init(&dict->buckets, sizeof(DictEntry), num_buckets);
    require_noerr(rval, finish);
    
    /* Initialize */
    dict->hash = hash;
    dict->cmp = cmp;
    dict->num_entries = 0;
    dict->resize_threshold = RESIZE_THRESHOLD(num_buckets);
    
    rval = KERN_SUCCESS;
    
finish:
    return rval;
}