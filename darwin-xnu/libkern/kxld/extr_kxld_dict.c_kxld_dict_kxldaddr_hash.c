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
typedef  int /*<<< orphan*/  u_int ;
typedef  int kxld_addr_t ;
struct TYPE_4__ {int nitems; } ;
struct TYPE_5__ {TYPE_1__ buckets; } ;
typedef  TYPE_2__ KXLDDict ;

/* Variables and functions */
 int /*<<< orphan*/  check (void const*) ; 

u_int
kxld_dict_kxldaddr_hash(const KXLDDict *dict, const void *_key)
{
    kxld_addr_t key = *(const kxld_addr_t *) _key;

    check(_key);

    return (u_int) (key % dict->buckets.nitems);
}