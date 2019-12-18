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
typedef  int /*<<< orphan*/  ia64_insn ;

/* Variables and functions */
 char* ext_imms_scaled (struct ia64_operand const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char*
ext_immsm1 (const struct ia64_operand *self, ia64_insn code, ia64_insn *valuep)
{
  const char *res = ext_imms_scaled (self, code, valuep, 0);

  ++*valuep;
  return res;
}