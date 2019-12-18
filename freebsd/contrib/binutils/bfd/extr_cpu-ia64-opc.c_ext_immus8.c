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
struct ia64_operand {int dummy; } ;
typedef  int ia64_insn ;

/* Variables and functions */
 char* ext_immu (struct ia64_operand const*,int,int*) ; 

__attribute__((used)) static const char*
ext_immus8 (const struct ia64_operand *self, ia64_insn code, ia64_insn *valuep)
{
  const char *result;

  result = ext_immu (self, code, valuep);
  if (result)
    return result;

  *valuep = *valuep << 3;
  return 0;
}