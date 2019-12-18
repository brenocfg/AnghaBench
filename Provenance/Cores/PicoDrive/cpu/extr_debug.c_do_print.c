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
struct pdb_cpu {scalar_t__ type; TYPE_1__* context; int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int* sh2irqi; int* sh2irq_mask; } ;
struct TYPE_3__ {int pc; int sr; int* r; int gbr; int vbr; size_t is_slave; int cycles_done; int cycles_aim; } ;
typedef  TYPE_1__ SH2 ;

/* Variables and functions */
 int CMDRET_DONE ; 
 int /*<<< orphan*/  EL_STATUS ; 
 scalar_t__ PDBCT_SH2 ; 
 TYPE_2__ Pico32x ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int,...) ; 

__attribute__((used)) static int do_print(struct pdb_cpu *cpu, const char *args)
{
  elprintf(EL_STATUS, "cpu %d (%s)", cpu->id, cpu->name);
#ifndef NO_32X
  if (cpu->type == PDBCT_SH2) {
    SH2 *sh2 = cpu->context;
    int i;
    printf("PC,SR %08x,     %03x\n", sh2->pc, sh2->sr & 0x3ff);
    for (i = 0; i < 16/2; i++)
      printf("R%d,%2d %08x,%08x\n", i, i + 8, sh2->r[i], sh2->r[i + 8]);
    printf("gb,vb %08x,%08x\n", sh2->gbr, sh2->vbr);
    printf("IRQs/mask:        %02x/%02x\n", Pico32x.sh2irqi[sh2->is_slave],
      Pico32x.sh2irq_mask[sh2->is_slave]);
    printf("cycles %d/%d (%d)\n", sh2->cycles_done, sh2->cycles_aim, (signed int)sh2->sr >> 12);
  }
#endif
  return CMDRET_DONE;
}