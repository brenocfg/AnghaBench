#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int X_op; scalar_t__ X_add_number; int /*<<< orphan*/  X_add_symbol; int /*<<< orphan*/  X_unsigned; } ;
struct fde_entry {scalar_t__ return_column; scalar_t__ signal_frame; scalar_t__ per_encoding; scalar_t__ lsda_encoding; struct cfi_insn_data* data; TYPE_4__ personality; } ;
struct cie_entry {scalar_t__ return_column; scalar_t__ signal_frame; scalar_t__ per_encoding; scalar_t__ lsda_encoding; struct cfi_insn_data* last; struct cfi_insn_data* first; TYPE_4__ personality; struct cie_entry* next; } ;
struct TYPE_6__ {int /*<<< orphan*/  reg2; int /*<<< orphan*/  reg1; } ;
struct TYPE_5__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  reg; } ;
struct TYPE_7__ {int /*<<< orphan*/  i; int /*<<< orphan*/  r; TYPE_2__ rr; TYPE_1__ ri; } ;
struct cfi_insn_data {int insn; struct cfi_insn_data* next; TYPE_3__ u; } ;

/* Variables and functions */
#define  CFI_escape 140 
#define  DW_CFA_advance_loc 139 
#define  DW_CFA_def_cfa 138 
#define  DW_CFA_def_cfa_offset 137 
#define  DW_CFA_def_cfa_register 136 
#define  DW_CFA_offset 135 
#define  DW_CFA_register 134 
#define  DW_CFA_remember_state 133 
#define  DW_CFA_restore 132 
#define  DW_CFA_same_value 131 
#define  DW_CFA_undefined 130 
 scalar_t__ DW_EH_PE_omit ; 
#define  O_constant 129 
#define  O_symbol 128 
 int /*<<< orphan*/  abort () ; 
 struct cie_entry* cie_root ; 
 int /*<<< orphan*/  output_cie (struct cie_entry*) ; 
 struct cie_entry* xmalloc (int) ; 

__attribute__((used)) static struct cie_entry *
select_cie_for_fde (struct fde_entry *fde, struct cfi_insn_data **pfirst)
{
  struct cfi_insn_data *i, *j;
  struct cie_entry *cie;

  for (cie = cie_root; cie; cie = cie->next)
    {
      if (cie->return_column != fde->return_column
	  || cie->signal_frame != fde->signal_frame
	  || cie->per_encoding != fde->per_encoding
	  || cie->lsda_encoding != fde->lsda_encoding)
	continue;
      if (cie->per_encoding != DW_EH_PE_omit)
	{
	  if (cie->personality.X_op != fde->personality.X_op
	      || cie->personality.X_add_number
		 != fde->personality.X_add_number)
	    continue;
	  switch (cie->personality.X_op)
	    {
	    case O_constant:
	      if (cie->personality.X_unsigned != fde->personality.X_unsigned)
		continue;
	      break;
	    case O_symbol:
	      if (cie->personality.X_add_symbol
		  != fde->personality.X_add_symbol)
		continue;
	      break;
	    default:
	      abort ();
	    }
	}
      for (i = cie->first, j = fde->data;
	   i != cie->last && j != NULL;
	   i = i->next, j = j->next)
	{
	  if (i->insn != j->insn)
	    goto fail;
	  switch (i->insn)
	    {
	    case DW_CFA_advance_loc:
	    case DW_CFA_remember_state:
	      /* We reached the first advance/remember in the FDE,
		 but did not reach the end of the CIE list.  */
	      goto fail;

	    case DW_CFA_offset:
	    case DW_CFA_def_cfa:
	      if (i->u.ri.reg != j->u.ri.reg)
		goto fail;
	      if (i->u.ri.offset != j->u.ri.offset)
		goto fail;
	      break;

	    case DW_CFA_register:
	      if (i->u.rr.reg1 != j->u.rr.reg1)
		goto fail;
	      if (i->u.rr.reg2 != j->u.rr.reg2)
		goto fail;
	      break;

	    case DW_CFA_def_cfa_register:
	    case DW_CFA_restore:
	    case DW_CFA_undefined:
	    case DW_CFA_same_value:
	      if (i->u.r != j->u.r)
		goto fail;
	      break;

	    case DW_CFA_def_cfa_offset:
	      if (i->u.i != j->u.i)
		goto fail;
	      break;

	    case CFI_escape:
	      /* Don't bother matching these for now.  */
	      goto fail;

	    default:
	      abort ();
	    }
	}

      /* Success if we reached the end of the CIE list, and we've either
	 run out of FDE entries or we've encountered an advance,
	 remember, or escape.  */
      if (i == cie->last
	  && (!j
	      || j->insn == DW_CFA_advance_loc
	      || j->insn == DW_CFA_remember_state
	      || j->insn == CFI_escape))
	{
	  *pfirst = j;
	  return cie;
	}

    fail:;
    }

  cie = xmalloc (sizeof (struct cie_entry));
  cie->next = cie_root;
  cie_root = cie;
  cie->return_column = fde->return_column;
  cie->signal_frame = fde->signal_frame;
  cie->per_encoding = fde->per_encoding;
  cie->lsda_encoding = fde->lsda_encoding;
  cie->personality = fde->personality;
  cie->first = fde->data;

  for (i = cie->first; i ; i = i->next)
    if (i->insn == DW_CFA_advance_loc
	|| i->insn == DW_CFA_remember_state
	|| i->insn == CFI_escape)
      break;

  cie->last = i;
  *pfirst = i;
   
  output_cie (cie);

  return cie;
}