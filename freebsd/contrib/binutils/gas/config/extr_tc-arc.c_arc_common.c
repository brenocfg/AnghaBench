#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  valueT ;
struct TYPE_19__ {int local; TYPE_1__* bsym; TYPE_3__* sy_frag; } ;
typedef  TYPE_2__ symbolS ;
typedef  scalar_t__ segT ;
typedef  int /*<<< orphan*/  relax_substateT ;
typedef  int /*<<< orphan*/  offsetT ;
struct TYPE_20__ {int /*<<< orphan*/ * fr_symbol; } ;
struct TYPE_18__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSF_OBJECT ; 
 int /*<<< orphan*/  SKIP_WHITESPACE () ; 
 int /*<<< orphan*/  S_CLEAR_EXTERNAL (TYPE_2__*) ; 
 int /*<<< orphan*/  S_GET_NAME (TYPE_2__*) ; 
 scalar_t__ S_GET_SEGMENT (TYPE_2__*) ; 
 scalar_t__ S_GET_VALUE (TYPE_2__*) ; 
 int /*<<< orphan*/  S_IS_COMMON (TYPE_2__*) ; 
 scalar_t__ S_IS_DEFINED (TYPE_2__*) ; 
 int /*<<< orphan*/  S_SET_ALIGN (TYPE_2__*,int) ; 
 int /*<<< orphan*/  S_SET_EXTERNAL (TYPE_2__*) ; 
 int /*<<< orphan*/  S_SET_SEGMENT (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  S_SET_SIZE (TYPE_2__*,int) ; 
 int /*<<< orphan*/  S_SET_VALUE (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  as_bad (char*) ; 
 int /*<<< orphan*/  as_warn (char*,...) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ bfd_com_section_ptr ; 
 scalar_t__ bss_section ; 
 int /*<<< orphan*/  demand_empty_rest_of_line () ; 
 int /*<<< orphan*/  frag_align (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* frag_now ; 
 char* frag_var (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int get_absolute_expression () ; 
 char get_symbol_end () ; 
 int /*<<< orphan*/  ignore_rest_of_line () ; 
 char* input_line_pointer ; 
 scalar_t__ now_seg ; 
 int now_subseg ; 
 int /*<<< orphan*/  record_alignment (scalar_t__,int) ; 
 int /*<<< orphan*/  rs_org ; 
 int /*<<< orphan*/  subseg_set (scalar_t__,int) ; 
 TYPE_2__* symbol_find_or_make (char*) ; 
 TYPE_3__ zero_address_frag ; 

__attribute__((used)) static void
arc_common (int localScope)
{
  char *name;
  char c;
  char *p;
  int align, size;
  symbolS *symbolP;

  name = input_line_pointer;
  c = get_symbol_end ();
  /* just after name is now '\0'  */
  p = input_line_pointer;
  *p = c;
  SKIP_WHITESPACE ();

  if (*input_line_pointer != ',')
    {
      as_bad ("expected comma after symbol name");
      ignore_rest_of_line ();
      return;
    }

  input_line_pointer++;		/* skip ','  */
  size = get_absolute_expression ();

  if (size < 0)
    {
      as_bad ("negative symbol length");
      ignore_rest_of_line ();
      return;
    }

  *p = 0;
  symbolP = symbol_find_or_make (name);
  *p = c;

  if (S_IS_DEFINED (symbolP) && ! S_IS_COMMON (symbolP))
    {
      as_bad ("ignoring attempt to re-define symbol");
      ignore_rest_of_line ();
      return;
    }
  if (((int) S_GET_VALUE (symbolP) != 0) \
      && ((int) S_GET_VALUE (symbolP) != size))
    {
      as_warn ("length of symbol \"%s\" already %ld, ignoring %d",
	       S_GET_NAME (symbolP), (long) S_GET_VALUE (symbolP), size);
    }
  assert (symbolP->sy_frag == &zero_address_frag);

  /* Now parse the alignment field.  This field is optional for
     local and global symbols. Default alignment is zero.  */
  if (*input_line_pointer == ',')
    {
      input_line_pointer++;
      align = get_absolute_expression ();
      if (align < 0)
	{
	  align = 0;
	  as_warn ("assuming symbol alignment of zero");
	}
    }
  else
    align = 0;

  if (localScope != 0)
    {
      segT old_sec;
      int old_subsec;
      char *pfrag;

      old_sec    = now_seg;
      old_subsec = now_subseg;
      record_alignment (bss_section, align);
      subseg_set (bss_section, 0);  /* ??? subseg_set (bss_section, 1); ???  */

      if (align)
	/* Do alignment.  */
	frag_align (align, 0, 0);

      /* Detach from old frag.  */
      if (S_GET_SEGMENT (symbolP) == bss_section)
	symbolP->sy_frag->fr_symbol = NULL;

      symbolP->sy_frag = frag_now;
      pfrag = frag_var (rs_org, 1, 1, (relax_substateT) 0, symbolP,
			(offsetT) size, (char *) 0);
      *pfrag = 0;

      S_SET_SIZE       (symbolP, size);
      S_SET_SEGMENT    (symbolP, bss_section);
      S_CLEAR_EXTERNAL (symbolP);
      symbolP->local = 1;
      subseg_set (old_sec, old_subsec);
    }
  else
    {
      S_SET_VALUE    (symbolP, (valueT) size);
      S_SET_ALIGN    (symbolP, align);
      S_SET_EXTERNAL (symbolP);
      S_SET_SEGMENT  (symbolP, bfd_com_section_ptr);
    }

  symbolP->bsym->flags |= BSF_OBJECT;

  demand_empty_rest_of_line ();
}