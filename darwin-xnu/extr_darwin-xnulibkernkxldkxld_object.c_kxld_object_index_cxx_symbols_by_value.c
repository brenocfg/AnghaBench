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
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_3__ {int /*<<< orphan*/  symtab; } ;
typedef  TYPE_1__ KXLDObject ;

/* Variables and functions */
 int /*<<< orphan*/  kxld_symtab_index_cxx_symbols_by_value (int /*<<< orphan*/ ) ; 

kern_return_t 
kxld_object_index_cxx_symbols_by_value(KXLDObject *object)
{
    return kxld_symtab_index_cxx_symbols_by_value(object->symtab);
}