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
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_4__ {int /*<<< orphan*/  kext; scalar_t__ interface; } ;
typedef  TYPE_1__ KXLDKext ;
typedef  int /*<<< orphan*/  KXLDDict ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  check (TYPE_1__ const*) ; 
 int /*<<< orphan*/  export_symbols (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  export_symbols_through_interface (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish ; 
 int /*<<< orphan*/  require_noerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t 
kxld_kext_export_symbols(const KXLDKext *kext, 
    KXLDDict *defined_symbols_by_name,
    KXLDDict *obsolete_symbols_by_name,
    KXLDDict *defined_cxx_symbols_by_value)
{
    kern_return_t rval = KERN_FAILURE;

    check(kext);

    if (kext->interface) {
        rval = export_symbols_through_interface(kext->kext, kext->interface, 
            defined_symbols_by_name, obsolete_symbols_by_name,
            defined_cxx_symbols_by_value);
        require_noerr(rval, finish);
    } else {
        rval = export_symbols(kext->kext, defined_symbols_by_name,
            defined_cxx_symbols_by_value);
        require_noerr(rval, finish);
    }

    rval = KERN_SUCCESS;
finish:
    return rval;
}