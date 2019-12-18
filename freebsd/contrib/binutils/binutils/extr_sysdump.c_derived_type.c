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
 int /*<<< orphan*/  IT_dar_CODE ; 
 int /*<<< orphan*/  IT_dds_CODE ; 
 int /*<<< orphan*/  IT_den_CODE ; 
 int /*<<< orphan*/  IT_dfp_CODE ; 
 int /*<<< orphan*/  IT_dot_CODE ; 
 int /*<<< orphan*/  IT_dpp_CODE ; 
 int /*<<< orphan*/  IT_dpt_CODE ; 
 int /*<<< orphan*/  IT_dse_CODE ; 
 int /*<<< orphan*/  IT_dul_CODE ; 
 int /*<<< orphan*/  dump_symbol_info () ; 
 int /*<<< orphan*/  must (int /*<<< orphan*/ ) ; 
 scalar_t__ opt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tab (int,char*) ; 

__attribute__((used)) static void
derived_type (void)
{
  tab (1, "DERIVED TYPE");

  while (1)
    {
      if (opt (IT_dpp_CODE))
	{
	  dump_symbol_info ();
	  must (IT_dpp_CODE);
	}
      else if (opt (IT_dfp_CODE))
	{
	  dump_symbol_info ();
	  must (IT_dfp_CODE);
	}
      else if (opt (IT_den_CODE))
	{
	  dump_symbol_info ();
	  must (IT_den_CODE);
	}
      else if (opt (IT_den_CODE))
	{
	  dump_symbol_info ();
	  must (IT_den_CODE);
	}
      else if (opt (IT_dds_CODE))
	{
	  dump_symbol_info ();
	  must (IT_dds_CODE);
	}
      else if (opt (IT_dar_CODE))
	{
	}
      else if (opt (IT_dpt_CODE))
	{
	}
      else if (opt (IT_dul_CODE))
	{
	}
      else if (opt (IT_dse_CODE))
	{
	}
      else if (opt (IT_dot_CODE))
	{
	}
      else
	break;
    }

  tab (-1, "");
}