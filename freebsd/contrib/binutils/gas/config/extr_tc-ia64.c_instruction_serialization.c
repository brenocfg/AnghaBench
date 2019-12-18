#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ debug_dv; } ;
struct TYPE_3__ {scalar_t__ insn_srlz; } ;

/* Variables and functions */
 scalar_t__ STATE_SRLZ ; 
 scalar_t__ STATE_STOP ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__ md ; 
 TYPE_1__* regdeps ; 
 int regdepslen ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
instruction_serialization ()
{
  int i;
  if (md.debug_dv)
    fprintf (stderr, "  Instruction serialization\n");
  for (i = 0; i < regdepslen; i++)
    if (regdeps[i].insn_srlz == STATE_STOP)
      regdeps[i].insn_srlz = STATE_SRLZ;
}