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
struct gdbarch {int dummy; } ;
struct TYPE_2__ {int fp0; } ;

/* Variables and functions */
 TYPE_1__* mips_regnum (struct gdbarch*) ; 

__attribute__((used)) static int
mips_fpa0_regnum (struct gdbarch *gdbarch)
{
  return mips_regnum (gdbarch)->fp0 + 12;
}