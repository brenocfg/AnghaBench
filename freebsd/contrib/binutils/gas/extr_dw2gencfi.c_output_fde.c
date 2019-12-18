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
struct TYPE_4__ {int /*<<< orphan*/ * X_op_symbol; void* X_op; int /*<<< orphan*/ * X_add_symbol; scalar_t__ X_add_number; } ;
struct fde_entry {int lsda_encoding; TYPE_1__ lsda; int /*<<< orphan*/ * start_address; int /*<<< orphan*/ * end_address; } ;
struct cie_entry {int /*<<< orphan*/ * start_address; } ;
struct cfi_insn_data {struct cfi_insn_data* next; } ;
typedef  int offsetT ;
typedef  TYPE_1__ expressionS ;

/* Variables and functions */
 int /*<<< orphan*/  DW_CFA_nop ; 
 int DW_EH_PE_omit ; 
 int DW_EH_PE_pcrel ; 
 void* O_subtract ; 
 void* O_symbol ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  emit_expr (TYPE_1__*,int) ; 
 int encoding_size (int) ; 
 int /*<<< orphan*/  frag_align (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uleb128 (int) ; 
 int /*<<< orphan*/  output_cfi_insn (struct cfi_insn_data*) ; 
 int /*<<< orphan*/  symbol_set_value_now (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * symbol_temp_make () ; 
 void* symbol_temp_new_now () ; 
 int /*<<< orphan*/  tc_cfi_emit_pcrel_expr (TYPE_1__*,int) ; 

__attribute__((used)) static void
output_fde (struct fde_entry *fde, struct cie_entry *cie,
	    struct cfi_insn_data *first, int align)
{
  symbolS *after_size_address, *end_address;
  expressionS exp;
  offsetT augmentation_size;

  after_size_address = symbol_temp_make ();
  end_address = symbol_temp_make ();

  exp.X_op = O_subtract;
  exp.X_add_symbol = end_address;
  exp.X_op_symbol = after_size_address;
  exp.X_add_number = 0;
  emit_expr (&exp, 4);				/* Length.  */
  symbol_set_value_now (after_size_address);

  exp.X_add_symbol = after_size_address;
  exp.X_op_symbol = cie->start_address;
  emit_expr (&exp, 4);				/* CIE offset.  */

#ifdef DIFF_EXPR_OK
  exp.X_add_symbol = fde->start_address;
  exp.X_op_symbol = symbol_temp_new_now ();
  emit_expr (&exp, 4);				/* Code offset.  */
#else
  exp.X_op = O_symbol;
  exp.X_add_symbol = fde->start_address;
  exp.X_op_symbol = NULL;
#ifdef tc_cfi_emit_pcrel_expr
  tc_cfi_emit_pcrel_expr (&exp, 4);		/* Code offset.  */
#else
  emit_expr (&exp, 4);				/* Code offset.  */
#endif
  exp.X_op = O_subtract;
#endif

  exp.X_add_symbol = fde->end_address;
  exp.X_op_symbol = fde->start_address;		/* Code length.  */
  emit_expr (&exp, 4);

  augmentation_size = encoding_size (fde->lsda_encoding);
  out_uleb128 (augmentation_size);		/* Augmentation size.  */

  if (fde->lsda_encoding != DW_EH_PE_omit)
    {
      exp = fde->lsda;
      if ((fde->lsda_encoding & 0x70) == DW_EH_PE_pcrel)
	{
#ifdef DIFF_EXPR_OK
	  exp.X_op = O_subtract;
	  exp.X_op_symbol = symbol_temp_new_now ();
	  emit_expr (&exp, augmentation_size);
#elif defined (tc_cfi_emit_pcrel_expr)
	  tc_cfi_emit_pcrel_expr (&exp, augmentation_size);
#else
	  abort ();
#endif
	}
      else
	emit_expr (&exp, augmentation_size);
    }

  for (; first; first = first->next)
    output_cfi_insn (first);

  frag_align (align, DW_CFA_nop, 0);
  symbol_set_value_now (end_address);
}