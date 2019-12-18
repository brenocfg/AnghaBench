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
typedef  int /*<<< orphan*/  pretty_printer ;

/* Variables and functions */
 int /*<<< orphan*/  pp_maybe_wrap_text (int /*<<< orphan*/ *,char const*,char const*) ; 
 int strlen (char const*) ; 

void
pp_base_string (pretty_printer *pp, const char *str)
{
  pp_maybe_wrap_text (pp, str, str + (str ? strlen (str) : 0));
}