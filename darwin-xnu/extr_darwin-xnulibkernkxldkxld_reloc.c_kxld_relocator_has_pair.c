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
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* reloc_has_pair ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ KXLDRelocator ;

/* Variables and functions */
 int /*<<< orphan*/  check (TYPE_1__ const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

boolean_t 
kxld_relocator_has_pair(const KXLDRelocator *relocator, u_int r_type)
{
    check(relocator);

    return relocator->reloc_has_pair(r_type);
}