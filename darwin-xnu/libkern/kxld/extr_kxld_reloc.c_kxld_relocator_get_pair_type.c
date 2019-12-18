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
struct TYPE_4__ {int /*<<< orphan*/  (* reloc_get_pair_type ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ KXLDRelocator ;

/* Variables and functions */
 int /*<<< orphan*/  check (TYPE_1__ const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

u_int 
kxld_relocator_get_pair_type(const KXLDRelocator *relocator,
    u_int prev_r_type)
{
    check(relocator);

    return relocator->reloc_get_pair_type(prev_r_type);
}