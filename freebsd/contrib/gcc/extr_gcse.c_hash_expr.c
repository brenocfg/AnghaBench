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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 unsigned int hash_rtx (int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static unsigned int
hash_expr (rtx x, enum machine_mode mode, int *do_not_record_p,
	   int hash_table_size)
{
  unsigned int hash;

  *do_not_record_p = 0;

  hash = hash_rtx (x, mode, do_not_record_p,
		   NULL,  /*have_reg_qty=*/false);
  return hash % hash_table_size;
}