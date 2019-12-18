#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int FIRST_PSEUDO_REGISTER ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 scalar_t__ reg_alloc_order ; 
 scalar_t__* reg_alloc_orders ; 
 int* regs_ever_live ; 

void
order_regs_for_local_alloc (void)
{
  static int last_order_nonleaf = 1;

  if (regs_ever_live[15] != last_order_nonleaf)
    {
      last_order_nonleaf = !last_order_nonleaf;
      memcpy ((char *) reg_alloc_order,
	      (const char *) reg_alloc_orders[last_order_nonleaf],
	      FIRST_PSEUDO_REGISTER * sizeof (int));
    }
}