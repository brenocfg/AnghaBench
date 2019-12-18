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
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mangle_obstack ; 
 int /*<<< orphan*/  obstack_grow (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * partially_mangled_name ; 
 int /*<<< orphan*/  partially_mangled_name_len ; 

__attribute__((used)) static void
restore_partially_mangled_name (void)
{
  if (partially_mangled_name)
    {
      obstack_grow (mangle_obstack, partially_mangled_name,
		    partially_mangled_name_len);
      free (partially_mangled_name);
      partially_mangled_name = NULL;
    }
}