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
typedef  TYPE_1__* dump_info_p ;
struct TYPE_4__ {int column; int /*<<< orphan*/  stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_maybe_newline (TYPE_1__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int strlen (char const*) ; 

void
dump_string (dump_info_p di, const char *string)
{
  dump_maybe_newline (di);
  fprintf (di->stream, "%-13s ", string);
  if (strlen (string) > 13)
    di->column += strlen (string) + 1;
  else
    di->column += 14;
}