#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  symbolS ;
struct TYPE_4__ {int /*<<< orphan*/ * X_op_symbol; void* X_op; scalar_t__ X_add_number; int /*<<< orphan*/ * X_add_symbol; } ;
struct cie_entry {int per_encoding; int lsda_encoding; int return_column; struct cfi_insn_data* last; struct cfi_insn_data* first; TYPE_1__ personality; scalar_t__ signal_frame; void* start_address; } ;
struct cfi_insn_data {struct cfi_insn_data* next; } ;
typedef  int offsetT ;
typedef  TYPE_1__ expressionS ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF2_CIE_DATA_ALIGNMENT ; 
 int DWARF2_LINE_MIN_INSN_LENGTH ; 
 int /*<<< orphan*/  DW_CFA_nop ; 
 int DW_CIE_VERSION ; 
 int DW_EH_PE_omit ; 
 int DW_EH_PE_pcrel ; 
 int DW_EH_PE_sdata4 ; 
 void* O_subtract ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  emit_expr (TYPE_1__*,int) ; 
 int encoding_size (int) ; 
 int /*<<< orphan*/  frag_align (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_four (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_one (int) ; 
 int /*<<< orphan*/  out_sleb128 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uleb128 (int) ; 
 int /*<<< orphan*/  output_cfi_insn (struct cfi_insn_data*) ; 
 int /*<<< orphan*/  symbol_set_value_now (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * symbol_temp_make () ; 
 void* symbol_temp_new_now () ; 
 int /*<<< orphan*/  tc_cfi_emit_pcrel_expr (TYPE_1__*,int) ; 

__attribute__((used)) static void
output_cie (struct cie_entry *cie)
{
  symbolS *after_size_address, *end_address;
  expressionS exp;
  struct cfi_insn_data *i;
  offsetT augmentation_size;

  cie->start_address = symbol_temp_new_now ();
  after_size_address = symbol_temp_make ();
  end_address = symbol_temp_make ();

  exp.X_op = O_subtract;
  exp.X_add_symbol = end_address;
  exp.X_op_symbol = after_size_address;
  exp.X_add_number = 0;

  emit_expr (&exp, 4);				/* Length.  */
  symbol_set_value_now (after_size_address);
  out_four (0);					/* CIE id.  */
  out_one (DW_CIE_VERSION);			/* Version.  */
  out_one ('z');				/* Augmentation.  */
  if (cie->per_encoding != DW_EH_PE_omit)
    out_one ('P');
  if (cie->lsda_encoding != DW_EH_PE_omit)
    out_one ('L');
  out_one ('R');
  if (cie->signal_frame)
    out_one ('S');
  out_one (0);
  out_uleb128 (DWARF2_LINE_MIN_INSN_LENGTH);	/* Code alignment.  */
  out_sleb128 (DWARF2_CIE_DATA_ALIGNMENT);	/* Data alignment.  */
  if (DW_CIE_VERSION == 1)			/* Return column.  */
    out_one (cie->return_column);
  else
    out_uleb128 (cie->return_column);
  augmentation_size = 1 + (cie->lsda_encoding != DW_EH_PE_omit);
  if (cie->per_encoding != DW_EH_PE_omit)
    augmentation_size += 1 + encoding_size (cie->per_encoding);
  out_uleb128 (augmentation_size);		/* Augmentation size.  */
  if (cie->per_encoding != DW_EH_PE_omit)
    {
      offsetT size = encoding_size (cie->per_encoding);
      out_one (cie->per_encoding);
      exp = cie->personality;
      if ((cie->per_encoding & 0x70) == DW_EH_PE_pcrel)
	{
#ifdef DIFF_EXPR_OK
	  exp.X_op = O_subtract;
	  exp.X_op_symbol = symbol_temp_new_now ();
	  emit_expr (&exp, size);
#elif defined (tc_cfi_emit_pcrel_expr)
	  tc_cfi_emit_pcrel_expr (&exp, size);
#else
	  abort ();
#endif
	}
      else
	emit_expr (&exp, size);
    }
  if (cie->lsda_encoding != DW_EH_PE_omit)
    out_one (cie->lsda_encoding);
#if defined DIFF_EXPR_OK || defined tc_cfi_emit_pcrel_expr
  out_one (DW_EH_PE_pcrel | DW_EH_PE_sdata4);
#else
  out_one (DW_EH_PE_sdata4);
#endif

  if (cie->first)
    for (i = cie->first; i != cie->last; i = i->next)
      output_cfi_insn (i);

  frag_align (2, DW_CFA_nop, 0);
  symbol_set_value_now (end_address);
}