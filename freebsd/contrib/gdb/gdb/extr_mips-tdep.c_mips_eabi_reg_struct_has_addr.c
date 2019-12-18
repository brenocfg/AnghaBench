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
typedef  enum type_code { ____Placeholder_type_code } type_code ;

/* Variables and functions */
 int TYPE_CODE (int /*<<< orphan*/ ) ; 
 int TYPE_CODE_STRUCT ; 
 int TYPE_CODE_UNION ; 
 int TYPE_LENGTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_typedef (struct type*) ; 
 int /*<<< orphan*/  current_gdbarch ; 
 struct gdbarch_tdep* gdbarch_tdep (int /*<<< orphan*/ ) ; 
 int mips_saved_regsize (struct gdbarch_tdep*) ; 

__attribute__((used)) static int
mips_eabi_reg_struct_has_addr (int gcc_p, struct type *type)
{
  enum type_code typecode = TYPE_CODE (check_typedef (type));
  int len = TYPE_LENGTH (check_typedef (type));
  struct gdbarch_tdep *tdep = gdbarch_tdep (current_gdbarch);

  if (typecode == TYPE_CODE_STRUCT || typecode == TYPE_CODE_UNION)
    return (len > mips_saved_regsize (tdep));

  return 0;
}