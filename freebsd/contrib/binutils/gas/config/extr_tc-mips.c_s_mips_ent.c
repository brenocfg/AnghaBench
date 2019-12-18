#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  symbolS ;
typedef  int /*<<< orphan*/  procS ;
struct TYPE_6__ {int /*<<< orphan*/ * func_sym; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSF_FUNCTION ; 
 scalar_t__ DEBUG_STABS ; 
 scalar_t__ ISDIGIT (char) ; 
 int SEC_CODE ; 
 int /*<<< orphan*/  SKIP_WHITESPACE () ; 
 int /*<<< orphan*/  S_GET_NAME (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ) ; 
 int bfd_get_section_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ cur_proc ; 
 TYPE_2__* cur_proc_ptr ; 
 scalar_t__ debug_type ; 
 int /*<<< orphan*/  demand_empty_rest_of_line () ; 
 int /*<<< orphan*/  get_number () ; 
 int /*<<< orphan*/ * get_symbol () ; 
 char* input_line_pointer ; 
 int /*<<< orphan*/  memset (TYPE_2__*,char,int) ; 
 scalar_t__ mips_cprestore_valid ; 
 scalar_t__ mips_frame_reg_valid ; 
 int /*<<< orphan*/  now_seg ; 
 int /*<<< orphan*/  numprocs ; 
 int /*<<< orphan*/  stabs_generate_asm_func (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdoutput ; 
 TYPE_1__* symbol_get_bfdsym (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
s_mips_ent (int aent)
{
  symbolS *symbolP;

  symbolP = get_symbol ();
  if (*input_line_pointer == ',')
    ++input_line_pointer;
  SKIP_WHITESPACE ();
  if (ISDIGIT (*input_line_pointer)
      || *input_line_pointer == '-')
    get_number ();

  if ((bfd_get_section_flags (stdoutput, now_seg) & SEC_CODE) == 0)
    as_warn (_(".ent or .aent not in text section."));

  if (!aent && cur_proc_ptr)
    as_warn (_("missing .end"));

  if (!aent)
    {
      /* This function needs its own .frame and .cprestore directives.  */
      mips_frame_reg_valid = 0;
      mips_cprestore_valid = 0;

      cur_proc_ptr = &cur_proc;
      memset (cur_proc_ptr, '\0', sizeof (procS));

      cur_proc_ptr->func_sym = symbolP;

      symbol_get_bfdsym (symbolP)->flags |= BSF_FUNCTION;

      ++numprocs;

      if (debug_type == DEBUG_STABS)
        stabs_generate_asm_func (S_GET_NAME (symbolP),
				 S_GET_NAME (symbolP));
    }

  demand_empty_rest_of_line ();
}