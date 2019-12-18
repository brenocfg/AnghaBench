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
struct TYPE_2__ {scalar_t__ unwind_check; } ;

/* Variables and functions */
 int /*<<< orphan*/  as_bad (char*,char const*,char const*) ; 
 int /*<<< orphan*/  as_warn (char*,char const*,char const*) ; 
 int /*<<< orphan*/  ignore_rest_of_line () ; 
 TYPE_1__ md ; 
 scalar_t__ unwind_check_warning ; 

__attribute__((used)) static int
unwind_diagnostic (const char * region, const char *directive)
{
  if (md.unwind_check == unwind_check_warning)
    {
      as_warn (".%s outside of %s", directive, region);
      return -1;
    }
  else
    {
      as_bad (".%s outside of %s", directive, region);
      ignore_rest_of_line ();
      return 0;
    }
}