#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  cxx_pp ; 
 int /*<<< orphan*/  pp_decimal_int (int /*<<< orphan*/ ,int) ; 
 char const* pp_formatted_text (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_string (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  reinit_cxx_pp () ; 

__attribute__((used)) static const char *
parm_to_string (int p)
{
  reinit_cxx_pp ();
  if (p < 0)
    pp_string (cxx_pp, "'this'");
  else
    pp_decimal_int (cxx_pp, p + 1);
  return pp_formatted_text (cxx_pp);
}