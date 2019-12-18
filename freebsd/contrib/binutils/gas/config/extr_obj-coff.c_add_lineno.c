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
struct TYPE_4__ {int /*<<< orphan*/  offset; } ;
struct TYPE_3__ {int line_number; TYPE_2__ u; } ;
struct line_no {TYPE_1__ l; int /*<<< orphan*/ * frag; struct line_no* next; } ;
typedef  int /*<<< orphan*/  fragS ;
typedef  int /*<<< orphan*/  addressT ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coff_n_line_nos ; 
 int /*<<< orphan*/  current_lineno_sym ; 
 struct line_no* line_nos ; 
 struct line_no* xmalloc (int) ; 

__attribute__((used)) static void
add_lineno (fragS * frag, addressT offset, int num)
{
  struct line_no * new_line = xmalloc (sizeof (* new_line));

  if (!current_lineno_sym)
    abort ();

#ifndef OBJ_XCOFF
  /* The native aix assembler accepts negative line number.  */

  if (num <= 0)
    {
      /* Zero is used as an end marker in the file.  */
      as_warn (_("Line numbers must be positive integers\n"));
      num = 1;
    }
#endif /* OBJ_XCOFF */
  new_line->next = line_nos;
  new_line->frag = frag;
  new_line->l.line_number = num;
  new_line->l.u.offset = offset;
  line_nos = new_line;
  coff_n_line_nos++;
}