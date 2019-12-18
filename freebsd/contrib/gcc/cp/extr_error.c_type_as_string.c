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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  cxx_pp ; 
 int /*<<< orphan*/  dump_type (int /*<<< orphan*/ ,int) ; 
 char const* pp_formatted_text (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_cxx_pp () ; 

const char *
type_as_string (tree typ, int flags)
{
  reinit_cxx_pp ();
  dump_type (typ, flags);
  return pp_formatted_text (cxx_pp);
}