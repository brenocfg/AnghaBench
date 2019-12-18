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
struct TYPE_2__ {scalar_t__ size; } ;

/* Variables and functions */
 TYPE_1__ inst ; 

__attribute__((used)) static void
do_it (void)
{
  /* There is no IT instruction in ARM mode.  We
     process it but do not generate code for it.  */
  inst.size = 0;
}