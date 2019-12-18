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
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ,char*,char const*) ; 
 char const* mips_arch_string ; 
 scalar_t__ strcasecmp (char const*,char const*) ; 

__attribute__((used)) static void
mips_set_option_string (const char **string_ptr, const char *new_value)
{
  if (*string_ptr != 0 && strcasecmp (*string_ptr, new_value) != 0)
    as_warn (_("A different %s was already specified, is now %s"),
	     string_ptr == &mips_arch_string ? "-march" : "-mtune",
	     new_value);

  *string_ptr = new_value;
}