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
typedef  int /*<<< orphan*/  gdb_fpregset_t ;

/* Variables and functions */
 int /*<<< orphan*/  mipsfbsd_supply_fpreg (char*,int) ; 

void 
supply_fpregset (gdb_fpregset_t *fpregs)
{
  mipsfbsd_supply_fpreg((char *)fpregs, -1);
}