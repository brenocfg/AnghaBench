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
typedef  int /*<<< orphan*/  symbolS ;
typedef  int subsegT ;
typedef  scalar_t__ segT ;
typedef  int /*<<< orphan*/  relax_substateT ;
typedef  int /*<<< orphan*/  offsetT ;
struct TYPE_4__ {int bss; } ;
struct TYPE_3__ {int /*<<< orphan*/ * fr_symbol; } ;

/* Variables and functions */
 scalar_t__ C_EXT ; 
 int /*<<< orphan*/  C_STAT ; 
 scalar_t__ OUTPUT_FLAVOR ; 
 int /*<<< orphan*/  SEC_ALLOC ; 
 int /*<<< orphan*/  SKIP_WHITESPACE () ; 
 scalar_t__ S_GET_DESC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_GET_NAME (int /*<<< orphan*/ *) ; 
 scalar_t__ S_GET_OTHER (int /*<<< orphan*/ *) ; 
 scalar_t__ S_GET_SEGMENT (int /*<<< orphan*/ *) ; 
 scalar_t__ S_GET_STORAGE_CLASS (int /*<<< orphan*/ *) ; 
 scalar_t__ S_GET_VALUE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_IS_DEFINED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_SET_SEGMENT (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  S_SET_SIZE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  S_SET_STORAGE_CLASS (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TC_IMPLICIT_LCOMM_ALIGNMENT (int,int) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  bfd_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 unsigned int bfd_get_gp_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_section_flags (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_target_aout_flavour ; 
 scalar_t__ bfd_target_ecoff_flavour ; 
 scalar_t__ bfd_target_elf_flavour ; 
 scalar_t__ bss_section ; 
 int /*<<< orphan*/  demand_empty_rest_of_line () ; 
 int /*<<< orphan*/  discard_rest_of_line () ; 
 int ffs (int) ; 
 int /*<<< orphan*/  frag_align (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frag_now ; 
 char* frag_var (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int get_absolute_expression () ; 
 char get_symbol_end () ; 
 int /*<<< orphan*/  ignore_rest_of_line () ; 
 char* input_line_pointer ; 
 scalar_t__* is_end_of_line ; 
 scalar_t__ now_seg ; 
 int now_subseg ; 
 int /*<<< orphan*/  record_alignment (scalar_t__,int) ; 
 int /*<<< orphan*/  rs_org ; 
 TYPE_2__* seg_info (scalar_t__) ; 
 int /*<<< orphan*/  stdoutput ; 
 scalar_t__ subseg_new (char*,int) ; 
 int /*<<< orphan*/  subseg_set (scalar_t__,int) ; 
 int /*<<< orphan*/ * symbol_find_or_make (char*) ; 
 TYPE_1__* symbol_get_frag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbol_set_frag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
s_score_lcomm (int bytes_p)
{
  char *name;
  char c;
  char *p;
  int temp;
  symbolS *symbolP;
  segT current_seg = now_seg;
  subsegT current_subseg = now_subseg;
  const int max_alignment = 15;
  int align = 0;
  segT bss_seg = bss_section;
  int needs_align = 0;

  name = input_line_pointer;
  c = get_symbol_end ();
  p = input_line_pointer;
  *p = c;

  if (name == p)
    {
      as_bad (_("expected symbol name"));
      discard_rest_of_line ();
      return;
    }

  SKIP_WHITESPACE ();

  /* Accept an optional comma after the name.  The comma used to be
     required, but Irix 5 cc does not generate it.  */
  if (*input_line_pointer == ',')
    {
      ++input_line_pointer;
      SKIP_WHITESPACE ();
    }

  if (is_end_of_line[(unsigned char)*input_line_pointer])
    {
      as_bad (_("missing size expression"));
      return;
    }

  if ((temp = get_absolute_expression ()) < 0)
    {
      as_warn (_("BSS length (%d) < 0 ignored"), temp);
      ignore_rest_of_line ();
      return;
    }

#if defined (TC_SCORE)
  if (OUTPUT_FLAVOR == bfd_target_ecoff_flavour || OUTPUT_FLAVOR == bfd_target_elf_flavour)
    {
      /* For Score and Alpha ECOFF or ELF, small objects are put in .sbss.  */
      if ((unsigned)temp <= bfd_get_gp_size (stdoutput))
        {
          bss_seg = subseg_new (".sbss", 1);
          seg_info (bss_seg)->bss = 1;
#ifdef BFD_ASSEMBLER
          if (!bfd_set_section_flags (stdoutput, bss_seg, SEC_ALLOC))
            as_warn (_("error setting flags for \".sbss\": %s"), bfd_errmsg (bfd_get_error ()));
#endif
        }
    }
#endif

  SKIP_WHITESPACE ();
  if (*input_line_pointer == ',')
    {
      ++input_line_pointer;
      SKIP_WHITESPACE ();

      if (is_end_of_line[(unsigned char)*input_line_pointer])
        {
          as_bad (_("missing alignment"));
          return;
        }
      else
        {
          align = get_absolute_expression ();
          needs_align = 1;
        }
    }

  if (!needs_align)
    {
      TC_IMPLICIT_LCOMM_ALIGNMENT (temp, align);

      /* Still zero unless TC_IMPLICIT_LCOMM_ALIGNMENT set it.  */
      if (align)
        record_alignment (bss_seg, align);
    }

  if (needs_align)
    {
      if (bytes_p)
        {
          /* Convert to a power of 2.  */
          if (align != 0)
            {
              unsigned int i;

              for (i = 0; align != 0; align >>= 1, ++i)
                ;
              align = i - 1;
            }
        }

      if (align > max_alignment)
        {
          align = max_alignment;
          as_warn (_("alignment too large; %d assumed"), align);
        }
      else if (align < 0)
        {
          align = 0;
          as_warn (_("alignment negative; 0 assumed"));
        }

      record_alignment (bss_seg, align);
    }
  else
    {
      /* Assume some objects may require alignment on some systems.  */
#if defined (TC_ALPHA) && ! defined (VMS)
      if (temp > 1)
        {
          align = ffs (temp) - 1;
          if (temp % (1 << align))
            abort ();
        }
#endif
    }

  *p = 0;
  symbolP = symbol_find_or_make (name);
  *p = c;

  if (
#if (defined (OBJ_AOUT) || defined (OBJ_MAYBE_AOUT) \
     || defined (OBJ_BOUT) || defined (OBJ_MAYBE_BOUT))
#ifdef BFD_ASSEMBLER
       (OUTPUT_FLAVOR != bfd_target_aout_flavour
        || (S_GET_OTHER (symbolP) == 0 && S_GET_DESC (symbolP) == 0)) &&
#else
       (S_GET_OTHER (symbolP) == 0 && S_GET_DESC (symbolP) == 0) &&
#endif
#endif
       (S_GET_SEGMENT (symbolP) == bss_seg || (!S_IS_DEFINED (symbolP) && S_GET_VALUE (symbolP) == 0)))
    {
      char *pfrag;

      subseg_set (bss_seg, 1);

      if (align)
        frag_align (align, 0, 0);

      /* Detach from old frag.  */
      if (S_GET_SEGMENT (symbolP) == bss_seg)
        symbol_get_frag (symbolP)->fr_symbol = NULL;

      symbol_set_frag (symbolP, frag_now);
      pfrag = frag_var (rs_org, 1, 1, (relax_substateT) 0, symbolP, (offsetT) temp, NULL);
      *pfrag = 0;


      S_SET_SEGMENT (symbolP, bss_seg);

#ifdef OBJ_COFF
      /* The symbol may already have been created with a preceding
         ".globl" directive -- be careful not to step on storage class
         in that case.  Otherwise, set it to static.  */
      if (S_GET_STORAGE_CLASS (symbolP) != C_EXT)
        {
          S_SET_STORAGE_CLASS (symbolP, C_STAT);
        }
#endif /* OBJ_COFF */

#ifdef S_SET_SIZE
      S_SET_SIZE (symbolP, temp);
#endif
    }
  else
    as_bad (_("symbol `%s' is already defined"), S_GET_NAME (symbolP));

  subseg_set (current_seg, current_subseg);

  demand_empty_rest_of_line ();
}