#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  symbolS ;
struct TYPE_5__ {int reg_mask; int reg_offset; int fpreg_mask; int leaf; int frame_offset; int frame_reg; int pc_reg; int /*<<< orphan*/ * isym; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSF_FUNCTION ; 
 scalar_t__ DEBUG_STABS ; 
 scalar_t__ ISDIGIT (char) ; 
 int SEC_CODE ; 
 int /*<<< orphan*/  SKIP_WHITESPACE () ; 
 int /*<<< orphan*/  S_GET_NAME (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ) ; 
 int bfd_get_section_flags (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ bss_section ; 
 TYPE_2__ cur_proc ; 
 TYPE_2__* cur_proc_ptr ; 
 scalar_t__ data_section ; 
 scalar_t__ debug_type ; 
 int /*<<< orphan*/  demand_empty_rest_of_line () ; 
 int /*<<< orphan*/  get_number () ; 
 int /*<<< orphan*/ * get_symbol () ; 
 char* input_line_pointer ; 
 scalar_t__ now_seg ; 
 int /*<<< orphan*/  numprocs ; 
 int /*<<< orphan*/  stabs_generate_asm_func (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdoutput ; 
 TYPE_1__* symbol_get_bfdsym (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
s_score_ent (int aent)
{
  symbolS *symbolP;
  int maybe_text;

  symbolP = get_symbol ();
  if (*input_line_pointer == ',')
    ++input_line_pointer;
  SKIP_WHITESPACE ();
  if (ISDIGIT (*input_line_pointer) || *input_line_pointer == '-')
    get_number ();

#ifdef BFD_ASSEMBLER
  if ((bfd_get_section_flags (stdoutput, now_seg) & SEC_CODE) != 0)
    maybe_text = 1;
  else
    maybe_text = 0;
#else
  if (now_seg != data_section && now_seg != bss_section)
    maybe_text = 1;
  else
    maybe_text = 0;
#endif
  if (!maybe_text)
    as_warn (_(".ent or .aent not in text section."));
  if (!aent && cur_proc_ptr)
    as_warn (_("missing .end"));
  if (!aent)
    {
      cur_proc_ptr = &cur_proc;
      cur_proc_ptr->reg_mask = 0xdeadbeaf;
      cur_proc_ptr->reg_offset = 0xdeadbeaf;
      cur_proc_ptr->fpreg_mask = 0xdeafbeaf;
      cur_proc_ptr->leaf = 0xdeafbeaf;
      cur_proc_ptr->frame_offset = 0xdeafbeaf;
      cur_proc_ptr->frame_reg = 0xdeafbeaf;
      cur_proc_ptr->pc_reg = 0xdeafbeaf;
      cur_proc_ptr->isym = symbolP;
      symbol_get_bfdsym (symbolP)->flags |= BSF_FUNCTION;
      ++numprocs;
      if (debug_type == DEBUG_STABS)
        stabs_generate_asm_func (S_GET_NAME (symbolP), S_GET_NAME (symbolP));
    }
  demand_empty_rest_of_line ();
}