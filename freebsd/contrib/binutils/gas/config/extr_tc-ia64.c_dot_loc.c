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
struct TYPE_2__ {int loc_directive_seen; } ;

/* Variables and functions */
 TYPE_1__ CURR_SLOT ; 
 int /*<<< orphan*/  dwarf2_directive_loc (int) ; 

__attribute__((used)) static void
dot_loc (int x)
{
  CURR_SLOT.loc_directive_seen = 1;
  dwarf2_directive_loc (x);
}