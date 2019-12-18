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
struct TYPE_2__ {scalar_t__ machine_dependent_reorg; } ;

/* Variables and functions */
 TYPE_1__ targetm ; 

__attribute__((used)) static bool
gate_handle_machine_reorg (void)
{
  return targetm.machine_dependent_reorg != 0;
}