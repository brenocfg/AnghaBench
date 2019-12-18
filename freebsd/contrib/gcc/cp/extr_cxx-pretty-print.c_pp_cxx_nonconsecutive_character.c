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
typedef  int /*<<< orphan*/  cxx_pretty_printer ;
struct TYPE_2__ {int /*<<< orphan*/  padding; } ;

/* Variables and functions */
 TYPE_1__* pp_base (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_character (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pp_cxx_whitespace (int /*<<< orphan*/ *) ; 
 char* pp_last_position_in_text (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_none ; 

__attribute__((used)) static inline void
pp_cxx_nonconsecutive_character (cxx_pretty_printer *pp, int c)
{
  const char *p = pp_last_position_in_text (pp);

  if (p != NULL && *p == c)
    pp_cxx_whitespace (pp);
  pp_character (pp, c);
  pp_base (pp)->padding = pp_none;
}