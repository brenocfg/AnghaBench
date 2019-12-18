#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* rtl; } ;
struct TYPE_6__ {TYPE_2__ il; } ;
struct TYPE_4__ {int /*<<< orphan*/  global_live_at_end; } ;

/* Variables and functions */
 TYPE_3__* ENTRY_BLOCK_PTR ; 
 int REGNO_REG_SET_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
ix86_eax_live_at_start_p (void)
{
  /* Cheat.  Don't bother working forward from ix86_function_regparm
     to the function type to whether an actual argument is located in
     eax.  Instead just look at cfg info, which is still close enough
     to correct at this point.  This gives false positives for broken
     functions that might use uninitialized data that happens to be
     allocated in eax, but who cares?  */
  return REGNO_REG_SET_P (ENTRY_BLOCK_PTR->il.rtl->global_live_at_end, 0);
}