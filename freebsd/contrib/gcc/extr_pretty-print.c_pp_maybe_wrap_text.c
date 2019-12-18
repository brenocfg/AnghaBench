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
 int /*<<< orphan*/  pp_append_text (int /*<<< orphan*/ *,char const*,char const*) ; 
 scalar_t__ pp_is_wrapping_line (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_wrap_text (int /*<<< orphan*/ *,char const*,char const*) ; 

__attribute__((used)) static inline void
pp_maybe_wrap_text (pretty_printer *pp, const char *start, const char *end)
{
  if (pp_is_wrapping_line (pp))
    pp_wrap_text (pp, start, end);
  else
    pp_append_text (pp, start, end);
}