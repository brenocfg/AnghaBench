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
struct TYPE_2__ {char* enumname; char* format; } ;

/* Variables and functions */
 TYPE_1__* defs ; 
 scalar_t__ excluded_rtx (int) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  puts (char*) ; 
 scalar_t__ special_rtx (int) ; 

__attribute__((used)) static void
genmacro (int idx)
{
  const char *p;
  int i;

  /* We write a macro that defines gen_rtx_RTLCODE to be an equivalent to
     gen_rtx_fmt_FORMAT where FORMAT is the RTX_FORMAT of RTLCODE.  */

  if (excluded_rtx (idx))
    /* Don't define a macro for this code.  */
    return;

  printf ("#define gen_rtx_%s%s(MODE",
	   special_rtx (idx) ? "raw_" : "", defs[idx].enumname);

  for (p = defs[idx].format, i = 0; *p != 0; p++)
    if (*p != '0')
      printf (", ARG%d", i++);

  printf (") \\\n  gen_rtx_fmt_%s (%s, (MODE)",
	  defs[idx].format, defs[idx].enumname);

  for (p = defs[idx].format, i = 0; *p != 0; p++)
    if (*p != '0')
      printf (", (ARG%d)", i++);

  puts (")");
}