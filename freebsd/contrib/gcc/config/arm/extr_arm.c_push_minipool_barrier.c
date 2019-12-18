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
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/  address; int /*<<< orphan*/  insn; } ;
typedef  TYPE_1__ Mfix ;
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 TYPE_1__* minipool_fix_head ; 
 TYPE_1__* minipool_fix_tail ; 
 int /*<<< orphan*/  minipool_obstack ; 
 scalar_t__ obstack_alloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
push_minipool_barrier (rtx insn, HOST_WIDE_INT address)
{
  Mfix * fix = (Mfix *) obstack_alloc (&minipool_obstack, sizeof (* fix));

  fix->insn = insn;
  fix->address = address;

  fix->next = NULL;
  if (minipool_fix_head != NULL)
    minipool_fix_tail->next = fix;
  else
    minipool_fix_head = fix;

  minipool_fix_tail = fix;
}