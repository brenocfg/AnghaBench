#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  x_dimen; } ;
struct TYPE_22__ {TYPE_3__ x_ary; } ;
struct TYPE_23__ {TYPE_4__ x_fcnary; } ;
union internal_auxent {TYPE_5__ x_sym; } ;
typedef  int /*<<< orphan*/  symbolS ;
struct TYPE_19__ {int offset; int /*<<< orphan*/ * sym; } ;
struct TYPE_24__ {TYPE_1__ u; scalar_t__ line_number; } ;
struct line_no {struct line_no* next; TYPE_6__ l; TYPE_2__* frag; } ;
typedef  int /*<<< orphan*/  stack ;
typedef  TYPE_6__ alent ;
struct TYPE_25__ {int /*<<< orphan*/  X_add_symbol; } ;
struct TYPE_20__ {int fr_address; } ;
struct TYPE_18__ {TYPE_6__* lineno; } ;
struct TYPE_17__ {int /*<<< orphan*/ * sym; } ;
struct TYPE_16__ {int flags; } ;
struct TYPE_15__ {int /*<<< orphan*/  output; } ;

/* Variables and functions */
 int BSF_FUNCTION ; 
 int BSF_NOT_AT_END ; 
 int BSF_SECTION_SYM ; 
 scalar_t__ C_BLOCK ; 
 scalar_t__ C_EFCN ; 
 scalar_t__ C_EOS ; 
 scalar_t__ C_EXT ; 
 scalar_t__ C_FCN ; 
 scalar_t__ C_FILE ; 
 scalar_t__ C_LABEL ; 
 scalar_t__ C_NT_WEAK ; 
 scalar_t__ C_NULL ; 
 scalar_t__ C_STAT ; 
 scalar_t__ C_WEAKEXT ; 
 int OCTETS_PER_BYTE ; 
 int /*<<< orphan*/  SA_SET_SYM_ENDNDX (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SA_SET_SYM_FSIZE (int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  SA_SET_SYM_TAGNDX (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SF_GET_DEBUG (int /*<<< orphan*/ *) ; 
 scalar_t__ SF_GET_FUNCTION (int /*<<< orphan*/ *) ; 
 scalar_t__ SF_GET_LOCAL (int /*<<< orphan*/ *) ; 
 scalar_t__ SF_GET_PROCESS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SF_GET_STATICS (int /*<<< orphan*/ *) ; 
 scalar_t__ SF_GET_TAG (int /*<<< orphan*/ *) ; 
 union internal_auxent* SYM_AUXENT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_CLEAR_EXTERNAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_GET_NAME (int /*<<< orphan*/ *) ; 
 int S_GET_NUMBER_AUXILIARY (int /*<<< orphan*/ *) ; 
 scalar_t__ S_GET_SEGMENT (int /*<<< orphan*/ *) ; 
 scalar_t__ S_GET_STORAGE_CLASS (int /*<<< orphan*/ *) ; 
 scalar_t__ S_GET_VALUE (int /*<<< orphan*/ *) ; 
 scalar_t__ S_IS_COMMON (int /*<<< orphan*/ *) ; 
 scalar_t__ S_IS_DEFINED (int /*<<< orphan*/ *) ; 
 scalar_t__ S_IS_EXTERNAL (int /*<<< orphan*/ *) ; 
 scalar_t__ S_IS_WEAK (int /*<<< orphan*/ *) ; 
 scalar_t__ S_IS_WEAKREFD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_SET_EXTERNAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_SET_NAME (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_SET_NUMBER_AUXILIARY (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  S_SET_SEGMENT (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  S_SET_STORAGE_CLASS (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  S_SET_VALUE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  abs_symbol ; 
 scalar_t__ absolute_section ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  as_fatal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  as_warn (char*,...) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  c_symbol_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  coff_add_linesym (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * coff_last_bf ; 
 int /*<<< orphan*/ * coff_last_function ; 
 TYPE_13__* coffsymbol (TYPE_11__*) ; 
 scalar_t__ current_lineno_sym ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_12__* seg_info (scalar_t__) ; 
 int /*<<< orphan*/ * stack_init (int,int) ; 
 scalar_t__ stack_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stack_push (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ streq (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ symbol_constant_p (int /*<<< orphan*/ *) ; 
 scalar_t__ symbol_equated_p (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * symbol_find_noref (int /*<<< orphan*/ ,int) ; 
 TYPE_11__* symbol_get_bfdsym (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbol_get_frag (int /*<<< orphan*/ *) ; 
 TYPE_10__* symbol_get_tc (int /*<<< orphan*/ *) ; 
 TYPE_8__* symbol_get_value_expression (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbol_set_frag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symbol_set_value_expression (int /*<<< orphan*/ *,TYPE_8__*) ; 
 int /*<<< orphan*/  symbol_used_in_reloc_p (int /*<<< orphan*/ *) ; 
 scalar_t__ text_section ; 
 scalar_t__ undefined_section ; 
 int /*<<< orphan*/  weak_altname2name (int /*<<< orphan*/ ) ; 
 scalar_t__ weak_is_altname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  weak_uniquify (int /*<<< orphan*/ ) ; 
 TYPE_6__* xmalloc (int) ; 

void
coff_frob_symbol (symbolS *symp, int *punt)
{
  static symbolS *last_tagP;
  static stack *block_stack;
  static symbolS *set_end;
  symbolS *next_set_end = NULL;

  if (symp == &abs_symbol)
    {
      *punt = 1;
      return;
    }

  if (current_lineno_sym)
    coff_add_linesym (NULL);

  if (!block_stack)
    block_stack = stack_init (512, sizeof (symbolS*));

#ifdef TE_PE
  if (S_GET_STORAGE_CLASS (symp) == C_NT_WEAK
      && ! S_IS_WEAK (symp)
      && weak_is_altname (S_GET_NAME (symp)))
    {
      /* This is a weak alternate symbol.  All processing of
	 PECOFFweak symbols is done here, through the alternate.  */
      symbolS *weakp = symbol_find_noref (weak_altname2name
					  (S_GET_NAME (symp)), 1);

      assert (weakp);
      assert (S_GET_NUMBER_AUXILIARY (weakp) == 1);

      if (! S_IS_WEAK (weakp))
	{
	  /* The symbol was turned from weak to strong.  Discard altname.  */
	  *punt = 1;
	  return;
	}
      else if (symbol_equated_p (weakp))
	{
	  /* The weak symbol has an alternate specified; symp is unneeded.  */
	  S_SET_STORAGE_CLASS (weakp, C_NT_WEAK);
	  SA_SET_SYM_TAGNDX (weakp,
	    symbol_get_value_expression (weakp)->X_add_symbol);

	  S_CLEAR_EXTERNAL (symp);
	  *punt = 1;
	  return;
	}
      else
	{
	  /* The weak symbol has been assigned an alternate value.
             Copy this value to symp, and set symp as weakp's alternate.  */
	  if (S_GET_STORAGE_CLASS (weakp) != C_NT_WEAK)
	    {
	      S_SET_STORAGE_CLASS (symp, S_GET_STORAGE_CLASS (weakp));
	      S_SET_STORAGE_CLASS (weakp, C_NT_WEAK);
	    }

	  if (S_IS_DEFINED (weakp))
	    {
	      /* This is a defined weak symbol.  Copy value information
	         from the weak symbol itself to the alternate symbol.  */
	      symbol_set_value_expression (symp,
					   symbol_get_value_expression (weakp));
	      symbol_set_frag (symp, symbol_get_frag (weakp));
	      S_SET_SEGMENT (symp, S_GET_SEGMENT (weakp));
	    }
	  else
	    {
	      /* This is an undefined weak symbol.
		 Define the alternate symbol to zero.  */
	      S_SET_VALUE (symp, 0);
	      S_SET_SEGMENT (symp, absolute_section);
	    }

	  S_SET_NAME (symp, weak_uniquify (S_GET_NAME (symp)));
	  S_SET_STORAGE_CLASS (symp, C_EXT);

	  S_SET_VALUE (weakp, 0);
	  S_SET_SEGMENT (weakp, undefined_section);
	}
    }
#else /* TE_PE */
  if (S_IS_WEAK (symp))
    S_SET_STORAGE_CLASS (symp, C_WEAKEXT);
#endif /* TE_PE */

  if (!S_IS_DEFINED (symp)
      && !S_IS_WEAK (symp)
      && S_GET_STORAGE_CLASS (symp) != C_STAT)
    S_SET_STORAGE_CLASS (symp, C_EXT);

  if (!SF_GET_DEBUG (symp))
    {
      symbolS * real;

      if (!SF_GET_LOCAL (symp)
	  && !SF_GET_STATICS (symp)
	  && S_GET_STORAGE_CLASS (symp) != C_LABEL
	  && symbol_constant_p (symp)
	  && (real = symbol_find_noref (S_GET_NAME (symp), 1))
	  && S_GET_STORAGE_CLASS (real) == C_NULL
	  && real != symp)
	{
	  c_symbol_merge (symp, real);
	  *punt = 1;
	  return;
	}

      if (!S_IS_DEFINED (symp) && !SF_GET_LOCAL (symp))
	{
	  assert (S_GET_VALUE (symp) == 0);
	  if (S_IS_WEAKREFD (symp))
	    *punt = 1;
	  else
	    S_SET_EXTERNAL (symp);
	}
      else if (S_GET_STORAGE_CLASS (symp) == C_NULL)
	{
	  if (S_GET_SEGMENT (symp) == text_section
	      && symp != seg_info (text_section)->sym)
	    S_SET_STORAGE_CLASS (symp, C_LABEL);
	  else
	    S_SET_STORAGE_CLASS (symp, C_STAT);
	}

      if (SF_GET_PROCESS (symp))
	{
	  if (S_GET_STORAGE_CLASS (symp) == C_BLOCK)
	    {
	      if (streq (S_GET_NAME (symp), ".bb"))
		stack_push (block_stack, (char *) &symp);
	      else
		{
		  symbolS *begin;

		  begin = *(symbolS **) stack_pop (block_stack);
		  if (begin == 0)
		    as_warn (_("mismatched .eb"));
		  else
		    next_set_end = begin;
		}
	    }

	  if (coff_last_function == 0 && SF_GET_FUNCTION (symp))
	    {
	      union internal_auxent *auxp;

	      coff_last_function = symp;
	      if (S_GET_NUMBER_AUXILIARY (symp) < 1)
		S_SET_NUMBER_AUXILIARY (symp, 1);
	      auxp = SYM_AUXENT (symp);
	      memset (auxp->x_sym.x_fcnary.x_ary.x_dimen, 0,
		      sizeof (auxp->x_sym.x_fcnary.x_ary.x_dimen));
	    }

	  if (S_GET_STORAGE_CLASS (symp) == C_EFCN)
	    {
	      if (coff_last_function == 0)
		as_fatal (_("C_EFCN symbol for %s out of scope"),
			  S_GET_NAME (symp));
	      SA_SET_SYM_FSIZE (coff_last_function,
				(long) (S_GET_VALUE (symp)
					- S_GET_VALUE (coff_last_function)));
	      next_set_end = coff_last_function;
	      coff_last_function = 0;
	    }
	}

      if (S_IS_EXTERNAL (symp))
	S_SET_STORAGE_CLASS (symp, C_EXT);
      else if (SF_GET_LOCAL (symp))
	*punt = 1;

      if (SF_GET_FUNCTION (symp))
	symbol_get_bfdsym (symp)->flags |= BSF_FUNCTION;
    }

  /* Double check weak symbols.  */
  if (S_IS_WEAK (symp) && S_IS_COMMON (symp))
    as_bad (_("Symbol `%s' can not be both weak and common"),
	    S_GET_NAME (symp));

  if (SF_GET_TAG (symp))
    last_tagP = symp;
  else if (S_GET_STORAGE_CLASS (symp) == C_EOS)
    next_set_end = last_tagP;

#ifdef OBJ_XCOFF
  /* This is pretty horrible, but we have to set *punt correctly in
     order to call SA_SET_SYM_ENDNDX correctly.  */
  if (! symbol_used_in_reloc_p (symp)
      && ((symbol_get_bfdsym (symp)->flags & BSF_SECTION_SYM) != 0
	  || (! (S_IS_EXTERNAL (symp) || S_IS_WEAK (symp))
	      && ! symbol_get_tc (symp)->output
	      && S_GET_STORAGE_CLASS (symp) != C_FILE)))
    *punt = 1;
#endif

  if (set_end != (symbolS *) NULL
      && ! *punt
      && ((symbol_get_bfdsym (symp)->flags & BSF_NOT_AT_END) != 0
	  || (S_IS_DEFINED (symp)
	      && ! S_IS_COMMON (symp)
	      && (! S_IS_EXTERNAL (symp) || SF_GET_FUNCTION (symp)))))
    {
      SA_SET_SYM_ENDNDX (set_end, symp);
      set_end = NULL;
    }

  if (next_set_end != NULL)
    {
      if (set_end != NULL)
	as_warn ("Warning: internal error: forgetting to set endndx of %s",
		 S_GET_NAME (set_end));
      set_end = next_set_end;
    }

#ifndef OBJ_XCOFF
  if (! *punt
      && S_GET_STORAGE_CLASS (symp) == C_FCN
      && streq (S_GET_NAME (symp), ".bf"))
    {
      if (coff_last_bf != NULL)
	SA_SET_SYM_ENDNDX (coff_last_bf, symp);
      coff_last_bf = symp;
    }
#endif
  if (coffsymbol (symbol_get_bfdsym (symp))->lineno)
    {
      int i;
      struct line_no *lptr;
      alent *l;

      lptr = (struct line_no *) coffsymbol (symbol_get_bfdsym (symp))->lineno;
      for (i = 0; lptr; lptr = lptr->next)
	i++;
      lptr = (struct line_no *) coffsymbol (symbol_get_bfdsym (symp))->lineno;

      /* We need i entries for line numbers, plus 1 for the first
	 entry which BFD will override, plus 1 for the last zero
	 entry (a marker for BFD).  */
      l = xmalloc ((i + 2) * sizeof (* l));
      coffsymbol (symbol_get_bfdsym (symp))->lineno = l;
      l[i + 1].line_number = 0;
      l[i + 1].u.sym = NULL;
      for (; i > 0; i--)
	{
	  if (lptr->frag)
	    lptr->l.u.offset += lptr->frag->fr_address / OCTETS_PER_BYTE;
	  l[i] = lptr->l;
	  lptr = lptr->next;
	}
    }
}