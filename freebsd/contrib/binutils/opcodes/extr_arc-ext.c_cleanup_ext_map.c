#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct arcExtMap {int dummy; } ;
struct ExtInstruction {struct ExtAuxRegister* name; } ;
struct ExtAuxRegister {int dummy; } ;
struct TYPE_3__ {struct ExtAuxRegister** condCodes; struct ExtAuxRegister** coreRegisters; struct ExtInstruction** instructions; struct ExtAuxRegister* auxRegisters; } ;

/* Variables and functions */
 int NUM_EXT_COND ; 
 int NUM_EXT_CORE ; 
 int NUM_EXT_INST ; 
 TYPE_1__ arc_extension_map ; 
 int /*<<< orphan*/  clean_aux_registers (struct ExtAuxRegister*) ; 
 int /*<<< orphan*/  free (struct ExtAuxRegister*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
cleanup_ext_map(void)
{
  struct ExtAuxRegister *r;
  struct ExtInstruction *insn;
  int i;

  /* clean aux reg structure  */
  r = arc_extension_map.auxRegisters;
  if (r)
    {
      (clean_aux_registers(r));
      free(r);
    }

  /* clean instructions  */
  for (i = 0; i < NUM_EXT_INST; i++)
    {
      insn = arc_extension_map.instructions[i];
      if (insn)
	free(insn->name);
    }

  /* clean core reg struct  */
  for (i = 0; i < NUM_EXT_CORE; i++)
    {
      if (arc_extension_map.coreRegisters[i])
	free(arc_extension_map.coreRegisters[i]);
    }

  for (i = 0; i < NUM_EXT_COND; i++) {
    if (arc_extension_map.condCodes[i])
      free(arc_extension_map.condCodes[i]);
  }

  memset(&arc_extension_map, 0, sizeof(struct arcExtMap));
}