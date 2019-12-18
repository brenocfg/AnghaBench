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
struct type {int dummy; } ;
struct TYPE_2__ {int fp0; } ;

/* Variables and functions */
 scalar_t__ BFD_ENDIAN_BIG ; 
 int NUM_REGS ; 
 scalar_t__ TARGET_BYTE_ORDER ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_FLT ; 
 int TYPE_LENGTH (struct type*) ; 
 int /*<<< orphan*/  current_gdbarch ; 
 TYPE_1__* mips_regnum (int /*<<< orphan*/ ) ; 
 int register_size (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mips_convert_register_p (int regnum, struct type *type)
{
  return (TARGET_BYTE_ORDER == BFD_ENDIAN_BIG
	  && register_size (current_gdbarch, regnum) == 4
	  && (regnum % NUM_REGS) >= mips_regnum (current_gdbarch)->fp0
	  && (regnum % NUM_REGS) < mips_regnum (current_gdbarch)->fp0 + 32
	  && TYPE_CODE (type) == TYPE_CODE_FLT && TYPE_LENGTH (type) == 8);
}