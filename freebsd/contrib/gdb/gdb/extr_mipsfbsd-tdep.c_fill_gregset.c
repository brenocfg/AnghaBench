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
typedef  int /*<<< orphan*/  gdb_gregset_t ;

/* Variables and functions */
 int /*<<< orphan*/  mipsfbsd_fill_reg (char*,int) ; 

void 
fill_gregset (gdb_gregset_t  *gregs, int regno)
{
  mipsfbsd_fill_reg ((char *)gregs, regno);
}