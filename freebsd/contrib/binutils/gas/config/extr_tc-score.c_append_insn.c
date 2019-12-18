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
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_2__ {int /*<<< orphan*/ * error; int /*<<< orphan*/  str; } ;

/* Variables and functions */
 scalar_t__ FAIL ; 
 int SUCCESS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ inst ; 
 int /*<<< orphan*/  parse_16_32_inst (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
append_insn (char *str, bfd_boolean gen_frag_p)
{
  int retval = SUCCESS;

  parse_16_32_inst (str, gen_frag_p);

  if (inst.error)
    {
      retval = (int) FAIL;
      as_bad (_("%s -- `%s'"), inst.error, inst.str);
      inst.error = NULL;
    }

  return retval;
}