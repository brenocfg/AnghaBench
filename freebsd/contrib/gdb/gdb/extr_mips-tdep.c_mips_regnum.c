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
struct mips_regnum {int dummy; } ;
struct gdbarch {int dummy; } ;
struct TYPE_2__ {struct mips_regnum const* regnum; } ;

/* Variables and functions */
 TYPE_1__* gdbarch_tdep (struct gdbarch*) ; 

const struct mips_regnum *
mips_regnum (struct gdbarch *gdbarch)
{
  return gdbarch_tdep (gdbarch)->regnum;
}