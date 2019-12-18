#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_3__ {int /*<<< orphan*/  c89name; int /*<<< orphan*/  realname; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  IDENTIFIER_POINTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_to_renaming_pragma_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* c89_mathlib_name_list ; 
 scalar_t__ flag_iso ; 
 int /*<<< orphan*/  flag_isoc94 ; 
 int /*<<< orphan*/  get_identifier (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ia64_hpux_add_pragma_builtin (tree func)
{
  size_t i;

  if (!flag_isoc94 && flag_iso)
    {
	for (i = 0; i < ARRAY_SIZE (c89_mathlib_name_list); i++)
	  {
	    if (!strcmp(c89_mathlib_name_list[i].realname,
			IDENTIFIER_POINTER (func)))
	      {
		add_to_renaming_pragma_list(func,
			get_identifier(c89_mathlib_name_list[i].c89name));
	      }
	  }
    }
}