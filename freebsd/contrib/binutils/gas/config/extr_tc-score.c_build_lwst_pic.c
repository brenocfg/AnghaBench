#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* bsym; } ;
typedef  TYPE_3__ symbolS ;
struct score_it {int dummy; } ;
struct TYPE_12__ {int X_add_number; TYPE_3__* X_add_symbol; } ;
typedef  TYPE_4__ expressionS ;
struct TYPE_9__ {int /*<<< orphan*/  type; } ;
struct TYPE_13__ {int bwarn; int /*<<< orphan*/  error; TYPE_1__ reloc; } ;
struct TYPE_10__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_RELOC_SCORE_GOT15 ; 
 scalar_t__ FAIL ; 
 int /*<<< orphan*/  FALSE ; 
 int MAX_LITERAL_POOL_SIZE ; 
 int RELAX_INST_NUM ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int append_insn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_relax_frag (struct score_it*,int,struct score_it*,int,TYPE_3__*) ; 
 TYPE_5__ inst ; 
 int /*<<< orphan*/  memcpy (struct score_it*,TYPE_5__*,int) ; 
 int nor1 ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,...) ; 

__attribute__((used)) static void
build_lwst_pic (int reg_rd, expressionS exp, const char *insn_name)
{
  symbolS *add_symbol = exp.X_add_symbol;
  int add_number = exp.X_add_number;
  struct score_it fix_insts[RELAX_INST_NUM];
  struct score_it var_insts[RELAX_INST_NUM];
  int fix_num = 0;
  int var_num = 0;
  char tmp[MAX_LITERAL_POOL_SIZE];
  int r1_bak;

  r1_bak = nor1;
  nor1 = 0;

  if ((add_number == 0) || (add_number >= -0x8000 && add_number <= 0x7fff))
    {
      fix_num = 1;
      var_num = 2;

      /* For an external symbol, two insns are generated;
         For a local symbol, three insns are generated.  */
      /* Fix part
         For an external symbol: lw rD, <sym>($gp)
                                 (BFD_RELOC_SCORE_GOT15)  */
      sprintf (tmp, "lw_pic r1, %s", add_symbol->bsym->name);
      if (append_insn (tmp, FALSE) == (int) FAIL)
        return;

      memcpy (&fix_insts[0], &inst, sizeof (struct score_it));

      /* Var part
	 For a local symbol :
         lw rD, <sym>($gp)    (BFD_RELOC_SCORE_GOT15)
	 addi rD, <sym>       (BFD_RELOC_GOT_LO16) */
      inst.reloc.type = BFD_RELOC_SCORE_GOT15;
      memcpy (&var_insts[0], &inst, sizeof (struct score_it));
      sprintf (tmp, "addi_s_pic r1, %s", add_symbol->bsym->name);
      if (append_insn (tmp, FALSE) == (int) FAIL)
        return;

      memcpy (&var_insts[1], &inst, sizeof (struct score_it));
      build_relax_frag (fix_insts, fix_num, var_insts, var_num, add_symbol);

      /* Insn 2 or Insn 3: lw/st rD, [r1, constant]  */
      sprintf (tmp, "%s r%d, [r1, %d]", insn_name, reg_rd, add_number);
      if (append_insn (tmp, TRUE) == (int) FAIL)
        return;

      /* Set bwarn as -1, so macro instruction itself will not be generated frag.  */
      inst.bwarn = -1;
    }
  else
    {
      inst.error = _("PIC code offset overflow (max 16 signed bits)");
      return;
    }

  nor1 = r1_bak;
}