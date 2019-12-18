#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  relax_substateT ;
struct TYPE_6__ {int* sizes; TYPE_1__* first_frag; scalar_t__ delay_slot_p; } ;
struct TYPE_5__ {scalar_t__ warn_about_macros; } ;
struct TYPE_4__ {int /*<<< orphan*/  fr_subtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  RELAX_DELAY_SLOT ; 
 int /*<<< orphan*/  RELAX_NOMACRO ; 
 int /*<<< orphan*/  RELAX_SECOND_LONGER ; 
 int /*<<< orphan*/  as_warn (char*,char const*) ; 
 char* macro_warning (int /*<<< orphan*/ ) ; 
 TYPE_3__ mips_macro_warning ; 
 TYPE_2__ mips_opts ; 

__attribute__((used)) static void
macro_end (void)
{
  if (mips_macro_warning.sizes[0] > 4 || mips_macro_warning.sizes[1] > 4)
    {
      relax_substateT subtype;

      /* Set up the relaxation warning flags.  */
      subtype = 0;
      if (mips_macro_warning.sizes[1] > mips_macro_warning.sizes[0])
	subtype |= RELAX_SECOND_LONGER;
      if (mips_opts.warn_about_macros)
	subtype |= RELAX_NOMACRO;
      if (mips_macro_warning.delay_slot_p)
	subtype |= RELAX_DELAY_SLOT;

      if (mips_macro_warning.sizes[0] > 4 && mips_macro_warning.sizes[1] > 4)
	{
	  /* Either the macro has a single implementation or both
	     implementations are longer than 4 bytes.  Emit the
	     warning now.  */
	  const char *msg = macro_warning (subtype);
	  if (msg != 0)
	    as_warn ("%s", msg);
	}
      else
	{
	  /* One implementation might need a warning but the other
	     definitely doesn't.  */
	  mips_macro_warning.first_frag->fr_subtype |= subtype;
	}
    }
}