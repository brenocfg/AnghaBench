#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int skipping; int in_expression; int /*<<< orphan*/  prevent_expansion; } ;
struct TYPE_8__ {scalar_t__ base; scalar_t__ cur; } ;
struct TYPE_10__ {TYPE_2__ state; TYPE_1__ out; TYPE_5__* directive; } ;
typedef  TYPE_3__ cpp_reader ;
struct TYPE_11__ {int flags; } ;

/* Variables and functions */
 int EXPAND ; 
 size_t T_DEFINE ; 
 size_t T_ELIF ; 
 size_t T_IF ; 
 int /*<<< orphan*/  _cpp_overlay_buffer (TYPE_3__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  _cpp_scan_out_logical_line (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_5__* dtable ; 

__attribute__((used)) static void
prepare_directive_trad (cpp_reader *pfile)
{
  if (pfile->directive != &dtable[T_DEFINE])
    {
      bool no_expand = (pfile->directive
			&& ! (pfile->directive->flags & EXPAND));
      bool was_skipping = pfile->state.skipping;

      pfile->state.in_expression = (pfile->directive == &dtable[T_IF]
				    || pfile->directive == &dtable[T_ELIF]);
      if (pfile->state.in_expression)
	pfile->state.skipping = false;

      if (no_expand)
	pfile->state.prevent_expansion++;
      _cpp_scan_out_logical_line (pfile, NULL);
      if (no_expand)
	pfile->state.prevent_expansion--;

      pfile->state.skipping = was_skipping;
      _cpp_overlay_buffer (pfile, pfile->out.base,
			   pfile->out.cur - pfile->out.base);
    }

  /* Stop ISO C from expanding anything.  */
  pfile->state.prevent_expansion++;
}