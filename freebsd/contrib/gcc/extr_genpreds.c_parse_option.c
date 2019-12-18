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
 int gen_constrs ; 
 int gen_header ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static bool
parse_option (const char *opt)
{
  if (!strcmp (opt, "-h"))
    {
      gen_header = true;
      return 1;
    }
  else if (!strcmp (opt, "-c"))
    {
      gen_constrs = true;
      return 1;
    }
  else
    return 0;
}