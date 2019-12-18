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
struct TYPE_4__ {long fx_pcrel_adjust; long fx_im_disp; int fx_size; int fx_r_type; scalar_t__ fx_subsy; scalar_t__ fx_addsy; scalar_t__ fx_addnumber; scalar_t__ fx_offset; scalar_t__ fx_where; scalar_t__ fx_frag; scalar_t__ fx_done; scalar_t__ fx_tcbit; scalar_t__ fx_pcrel; int /*<<< orphan*/  fx_line; int /*<<< orphan*/  fx_file; } ;
typedef  TYPE_1__ fixS ;

/* Variables and functions */
 int /*<<< orphan*/  TC_FIX_DATA_PRINT (int /*<<< orphan*/ ,TYPE_1__*) ; 
 char* bfd_get_reloc_code_name (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int indent_level ; 
 int /*<<< orphan*/  print_symbol_value_1 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 

void
print_fixup (fixS *fixp)
{
  indent_level = 1;
  fprintf (stderr, "fix %lx %s:%d", (long) fixp, fixp->fx_file, fixp->fx_line);
  if (fixp->fx_pcrel)
    fprintf (stderr, " pcrel");
  if (fixp->fx_pcrel_adjust)
    fprintf (stderr, " pcrel_adjust=%d", fixp->fx_pcrel_adjust);
  if (fixp->fx_im_disp)
    {
#ifdef TC_NS32K
      fprintf (stderr, " im_disp=%d", fixp->fx_im_disp);
#else
      fprintf (stderr, " im_disp");
#endif
    }
  if (fixp->fx_tcbit)
    fprintf (stderr, " tcbit");
  if (fixp->fx_done)
    fprintf (stderr, " done");
  fprintf (stderr, "\n    size=%d frag=%lx where=%ld offset=%lx addnumber=%lx",
	   fixp->fx_size, (long) fixp->fx_frag, (long) fixp->fx_where,
	   (long) fixp->fx_offset, (long) fixp->fx_addnumber);
  fprintf (stderr, "\n    %s (%d)", bfd_get_reloc_code_name (fixp->fx_r_type),
	   fixp->fx_r_type);
  if (fixp->fx_addsy)
    {
      fprintf (stderr, "\n   +<");
      print_symbol_value_1 (stderr, fixp->fx_addsy);
      fprintf (stderr, ">");
    }
  if (fixp->fx_subsy)
    {
      fprintf (stderr, "\n   -<");
      print_symbol_value_1 (stderr, fixp->fx_subsy);
      fprintf (stderr, ">");
    }
  fprintf (stderr, "\n");
#ifdef TC_FIX_DATA_PRINT
  TC_FIX_DATA_PRINT (stderr, fixp);
#endif
}