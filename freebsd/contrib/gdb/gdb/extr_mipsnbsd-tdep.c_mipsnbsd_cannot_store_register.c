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
struct TYPE_2__ {int fp_implementation_revision; } ;

/* Variables and functions */
 int ZERO_REGNUM ; 
 int /*<<< orphan*/  current_gdbarch ; 
 TYPE_1__* mips_regnum (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mipsnbsd_cannot_store_register (int regno)
{
  return (regno == ZERO_REGNUM
	  || regno == mips_regnum (current_gdbarch)->fp_implementation_revision);
}