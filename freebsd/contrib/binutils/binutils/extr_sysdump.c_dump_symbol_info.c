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
 int /*<<< orphan*/  IT_dbt_CODE ; 
 int /*<<< orphan*/  IT_dsy_CODE ; 
 int /*<<< orphan*/  IT_dty_CODE ; 
 int /*<<< orphan*/  derived_type () ; 
 int /*<<< orphan*/  must (int /*<<< orphan*/ ) ; 
 scalar_t__ opt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tab (int,char*) ; 

__attribute__((used)) static void
dump_symbol_info (void)
{
  tab (1, "SYMBOL INFO");

  while (opt (IT_dsy_CODE))
    {
      if (opt (IT_dty_CODE))
	{
	  must (IT_dbt_CODE);
	  derived_type ();
	  must (IT_dty_CODE);
	}
    }

  tab (-1, "");
}