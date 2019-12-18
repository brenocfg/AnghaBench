#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct linetable {size_t nitems; TYPE_1__* item; } ;
struct TYPE_2__ {int line; int pc; } ;
typedef  int CORE_ADDR ;

/* Variables and functions */

__attribute__((used)) static int
add_line (struct linetable *lt, int lineno, CORE_ADDR adr, int last)
{
  /* DEC c89 sometimes produces zero linenos which confuse gdb.
     Change them to something sensible. */
  if (lineno == 0)
    lineno = 1;
  if (last == 0)
    last = -2;			/* make sure we record first line */

  if (last == lineno)		/* skip continuation lines */
    return lineno;

  lt->item[lt->nitems].line = lineno;
  lt->item[lt->nitems++].pc = adr << 2;
  return lineno;
}