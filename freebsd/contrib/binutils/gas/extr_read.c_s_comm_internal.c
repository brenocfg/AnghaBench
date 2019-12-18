#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  valueT ;
typedef  int /*<<< orphan*/  symbolS ;
typedef  int offsetT ;
struct TYPE_6__ {scalar_t__ X_op; int /*<<< orphan*/  X_unsigned; } ;
typedef  TYPE_2__ expressionS ;
struct TYPE_7__ {TYPE_1__* arch_info; } ;
struct TYPE_5__ {int bits_per_address; } ;
typedef  int /*<<< orphan*/  S_GET_OTHER ;

/* Variables and functions */
 scalar_t__ O_absent ; 
 int /*<<< orphan*/  SKIP_WHITESPACE () ; 
 int /*<<< orphan*/  S_CLEAR_VOLATILE (int /*<<< orphan*/ *) ; 
 int S_GET_VALUE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_IS_COMMON (int /*<<< orphan*/ *) ; 
 scalar_t__ S_IS_DEFINED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_IS_VOLATILE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_SET_EXTERNAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_SET_SEGMENT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_SET_VALUE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  bfd_com_section_ptr ; 
 int /*<<< orphan*/  const_flag ; 
 int /*<<< orphan*/  demand_empty_rest_of_line () ; 
 scalar_t__ flag_mri ; 
 int get_absolute_expr (TYPE_2__*) ; 
 char get_symbol_end () ; 
 int /*<<< orphan*/  ignore_rest_of_line () ; 
 char* input_line_pointer ; 
 int /*<<< orphan*/  mri_comment_end (char*,char) ; 
 char* mri_comment_field (char*) ; 
 TYPE_3__* stdoutput ; 
 int /*<<< orphan*/ * stub1 (int,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/ * symbol_clone (int /*<<< orphan*/ *,int) ; 
 scalar_t__ symbol_equated_p (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * symbol_find_or_make (char*) ; 
 int /*<<< orphan*/  symbol_set_frag (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  undefined_section ; 
 int /*<<< orphan*/  zero_address_frag ; 

symbolS *
s_comm_internal (int param,
		 symbolS *(*comm_parse_extra) (int, symbolS *, addressT))
{
  char *name;
  char c;
  char *p;
  offsetT temp, size;
  symbolS *symbolP = NULL;
  char *stop = NULL;
  char stopc = 0;
  expressionS exp;

  if (flag_mri)
    stop = mri_comment_field (&stopc);

  name = input_line_pointer;
  c = get_symbol_end ();
  /* Just after name is now '\0'.  */
  p = input_line_pointer;
  *p = c;

  if (name == p)
    {
      as_bad (_("expected symbol name"));
      ignore_rest_of_line ();
      goto out;
    }

  SKIP_WHITESPACE ();

  /* Accept an optional comma after the name.  The comma used to be
     required, but Irix 5 cc does not generate it for .lcomm.  */
  if (*input_line_pointer == ',')
    input_line_pointer++;

  temp = get_absolute_expr (&exp);
  size = temp;
  size &= ((offsetT) 2 << (stdoutput->arch_info->bits_per_address - 1)) - 1;
  if (exp.X_op == O_absent)
    {
      as_bad (_("missing size expression"));
      ignore_rest_of_line ();
      goto out;
    }
  else if (temp != size || !exp.X_unsigned)
    {
      as_warn (_("size (%ld) out of range, ignored"), (long) temp);
      ignore_rest_of_line ();
      goto out;
    }

  *p = 0;
  symbolP = symbol_find_or_make (name);
  if ((S_IS_DEFINED (symbolP) || symbol_equated_p (symbolP))
      && !S_IS_COMMON (symbolP))
    {
      if (!S_IS_VOLATILE (symbolP))
	{
	  symbolP = NULL;
	  as_bad (_("symbol `%s' is already defined"), name);
	  *p = c;
	  ignore_rest_of_line ();
	  goto out;
	}
      symbolP = symbol_clone (symbolP, 1);
      S_SET_SEGMENT (symbolP, undefined_section);
      S_SET_VALUE (symbolP, 0);
      symbol_set_frag (symbolP, &zero_address_frag);
      S_CLEAR_VOLATILE (symbolP);
    }

  size = S_GET_VALUE (symbolP);
  if (size == 0)
    size = temp;
  else if (size != temp)
    as_warn (_("size of \"%s\" is already %ld; not changing to %ld"),
	     name, (long) size, (long) temp);

  *p = c;
  if (comm_parse_extra != NULL)
    symbolP = (*comm_parse_extra) (param, symbolP, size);
  else
    {
      S_SET_VALUE (symbolP, (valueT) size);
      S_SET_EXTERNAL (symbolP);
      S_SET_SEGMENT (symbolP, bfd_com_section_ptr);
#ifdef OBJ_VMS
      {
	extern int flag_one;
	if (size == 0 || !flag_one)
	  S_GET_OTHER (symbolP) = const_flag;
      }
#endif
    }

  demand_empty_rest_of_line ();
 out:
  if (flag_mri)
    mri_comment_end (stop, stopc);
  return symbolP;
}