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
struct asm_opcode {int tvalue; int avalue; int /*<<< orphan*/  (* aencode ) () ;int /*<<< orphan*/  (* tencode ) () ;int /*<<< orphan*/ * avariant; int /*<<< orphan*/ * tvariant; } ;
struct TYPE_2__ {int instruction; int cond; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_CPU_HAS_FEATURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BAD_FPU ; 
 int /*<<< orphan*/  _ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  arm_ops_hsh ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_variant ; 
 struct asm_opcode* hash_find (int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__ inst ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 
 scalar_t__ thumb_mode ; 

__attribute__((used)) static void
do_vfp_nsyn_opcode (const char *opname)
{
  const struct asm_opcode *opcode;
  
  opcode = hash_find (arm_ops_hsh, opname);

  if (!opcode)
    abort ();

  constraint (!ARM_CPU_HAS_FEATURE (cpu_variant,
                thumb_mode ? *opcode->tvariant : *opcode->avariant),
              _(BAD_FPU));

  if (thumb_mode)
    {
      inst.instruction = opcode->tvalue;
      opcode->tencode ();
    }
  else
    {
      inst.instruction = (inst.cond << 28) | opcode->avalue;
      opcode->aencode ();
    }
}