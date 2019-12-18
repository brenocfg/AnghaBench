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
struct TYPE_3__ {int /*<<< orphan*/ * ifld_table; } ;
typedef  TYPE_1__ CGEN_CPU_TABLE ;

/* Variables and functions */
 int /*<<< orphan*/ * mep_cgen_ifld_table ; 

__attribute__((used)) static void
build_ifield_table (CGEN_CPU_TABLE *cd)
{
  cd->ifld_table = & mep_cgen_ifld_table[0];
}