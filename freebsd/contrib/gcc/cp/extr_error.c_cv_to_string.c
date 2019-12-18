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
typedef  int /*<<< orphan*/  tree ;
struct TYPE_2__ {int /*<<< orphan*/  padding; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxx_pp ; 
 TYPE_1__* pp_base (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_before ; 
 int /*<<< orphan*/  pp_cxx_cv_qualifier_seq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char const* pp_formatted_text (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_none ; 
 int /*<<< orphan*/  reinit_cxx_pp () ; 

__attribute__((used)) static const char *
cv_to_string (tree p, int v)
{
  reinit_cxx_pp ();
  pp_base (cxx_pp)->padding = v ? pp_before : pp_none;
  pp_cxx_cv_qualifier_seq (cxx_pp, p);
  return pp_formatted_text (cxx_pp);
}