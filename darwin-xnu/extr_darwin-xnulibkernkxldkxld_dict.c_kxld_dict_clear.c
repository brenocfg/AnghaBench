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
struct TYPE_4__ {int /*<<< orphan*/  resize_buckets; int /*<<< orphan*/  buckets; scalar_t__ resize_threshold; scalar_t__ num_entries; int /*<<< orphan*/ * cmp; int /*<<< orphan*/ * hash; } ;
typedef  TYPE_1__ KXLDDict ;

/* Variables and functions */
 int /*<<< orphan*/  check (TYPE_1__*) ; 
 int /*<<< orphan*/  kxld_array_clear (int /*<<< orphan*/ *) ; 

void
kxld_dict_clear(KXLDDict *dict)
{
    check(dict);

    dict->hash = NULL;
    dict->cmp = NULL;
    dict->num_entries = 0;
    dict->resize_threshold = 0;
    kxld_array_clear(&dict->buckets);
    kxld_array_clear(&dict->resize_buckets);
}