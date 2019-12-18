#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ size; int /*<<< orphan*/  decl; } ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 unsigned int DECL_UID (int /*<<< orphan*/ ) ; 
 TYPE_1__* stack_vars ; 

__attribute__((used)) static int
stack_var_size_cmp (const void *a, const void *b)
{
  HOST_WIDE_INT sa = stack_vars[*(const size_t *)a].size;
  HOST_WIDE_INT sb = stack_vars[*(const size_t *)b].size;
  unsigned int uida = DECL_UID (stack_vars[*(const size_t *)a].decl);
  unsigned int uidb = DECL_UID (stack_vars[*(const size_t *)b].decl);

  if (sa < sb)
    return -1;
  if (sa > sb)
    return 1;
  /* For stack variables of the same size use the uid of the decl
     to make the sort stable.  */
  if (uida < uidb)
    return -1;
  if (uida > uidb)
    return 1;
  return 0;
}