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
struct type {int dummy; } ;
struct gdbarch_tdep {int dummy; } ;

/* Variables and functions */
 int TYPE_LENGTH (struct type*) ; 
 int /*<<< orphan*/  current_gdbarch ; 
 struct gdbarch_tdep* gdbarch_tdep (int /*<<< orphan*/ ) ; 
 int mips_saved_regsize (struct gdbarch_tdep*) ; 

__attribute__((used)) static int
mips_eabi_use_struct_convention (int gcc_p, struct type *type)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (current_gdbarch);
  return (TYPE_LENGTH (type) > 2 * mips_saved_regsize (tdep));
}