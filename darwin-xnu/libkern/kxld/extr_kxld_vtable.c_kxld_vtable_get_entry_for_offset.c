#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_3__ {int /*<<< orphan*/  entries; } ;
typedef  int /*<<< orphan*/  KXLDVTableEntry ;
typedef  TYPE_1__ KXLDVTable ;

/* Variables and functions */
 int /*<<< orphan*/  get_vtable_base_sizes (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/ * kxld_array_get_item (int /*<<< orphan*/ *,int) ; 

KXLDVTableEntry * 
kxld_vtable_get_entry_for_offset(const KXLDVTable *vtable, u_long offset, 
    boolean_t is_32_bit)
{
    KXLDVTableEntry *rval = NULL;
    u_int vtable_entry_size = 0;
    u_int vtable_header_size = 0;
    u_int vtable_entry_idx = 0;

    (void) get_vtable_base_sizes(is_32_bit, 
        &vtable_entry_size, &vtable_header_size);

    if (offset % vtable_entry_size) {
        goto finish;
    }

    vtable_entry_idx = (u_int) ((offset - vtable_header_size) / vtable_entry_size);
    rval = kxld_array_get_item(&vtable->entries, vtable_entry_idx);
finish:
    return rval;
}