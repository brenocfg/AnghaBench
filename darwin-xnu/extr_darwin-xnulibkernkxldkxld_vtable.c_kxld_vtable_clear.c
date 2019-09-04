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
struct TYPE_4__ {int /*<<< orphan*/  entries; int /*<<< orphan*/  is_patched; int /*<<< orphan*/ * name; int /*<<< orphan*/ * vtable; } ;
typedef  TYPE_1__ KXLDVTable ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  check (TYPE_1__*) ; 
 int /*<<< orphan*/  kxld_array_clear (int /*<<< orphan*/ *) ; 

void
kxld_vtable_clear(KXLDVTable *vtable)
{
    check(vtable);

    vtable->vtable = NULL;
    vtable->name = NULL;
    vtable->is_patched = FALSE;
    kxld_array_clear(&vtable->entries);
}