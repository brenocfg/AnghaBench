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
 scalar_t__ DECL_BASE_CONSTRUCTOR_P (int /*<<< orphan*/  const) ; 
 scalar_t__ DECL_COMPLETE_CONSTRUCTOR_P (int /*<<< orphan*/  const) ; 
 scalar_t__ DECL_MAYBE_IN_CHARGE_CONSTRUCTOR_P (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  write_string (char*) ; 

__attribute__((used)) static void
write_special_name_constructor (const tree ctor)
{
  if (DECL_BASE_CONSTRUCTOR_P (ctor))
    write_string ("C2");
  else
    {
      gcc_assert (DECL_COMPLETE_CONSTRUCTOR_P (ctor)
		  /* Even though we don't ever emit a definition of
		     the old-style destructor, we still have to
		     consider entities (like static variables) nested
		     inside it.  */
		  || DECL_MAYBE_IN_CHARGE_CONSTRUCTOR_P (ctor));
      write_string ("C1");
    }
}