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
typedef  int /*<<< orphan*/  c_pretty_printer ;

/* Variables and functions */
 scalar_t__ ISPRINT (int) ; 
 int /*<<< orphan*/  pp_character (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pp_scalar (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  pp_string (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
pp_c_char (c_pretty_printer *pp, int c)
{
  if (ISPRINT (c))
    {
      switch (c)
	{
	case '\\': pp_string (pp, "\\\\"); break;
	case '\'': pp_string (pp, "\\\'"); break;
	case '\"': pp_string (pp, "\\\""); break;
	default:   pp_character (pp, c);
	}
    }
  else
    pp_scalar (pp, "\\%03o", (unsigned) c);
}