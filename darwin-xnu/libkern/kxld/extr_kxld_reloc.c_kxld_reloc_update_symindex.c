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
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_3__ {scalar_t__ target_type; int /*<<< orphan*/  target; } ;
typedef  TYPE_1__ KXLDReloc ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ KXLD_TARGET_SYMBOLNUM ; 
 int /*<<< orphan*/  finish ; 
 int /*<<< orphan*/  require_action (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t 
kxld_reloc_update_symindex(KXLDReloc *reloc, u_int symindex)
{
    kern_return_t rval = KERN_FAILURE;

    require_action(reloc->target_type == KXLD_TARGET_SYMBOLNUM, 
        finish, rval = KERN_FAILURE);

    reloc->target = symindex;

    rval = KERN_SUCCESS;

finish:
    return rval;
}