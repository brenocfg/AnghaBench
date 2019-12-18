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
 char* _ (char*) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  try_help (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
specify_value (char const **var, char const *value, char const *option)
{
  if (*var && strcmp (*var, value) != 0)
    {
      error (0, 0, _("conflicting %s option value `%s'"), option, value);
      try_help (0, 0);
    }
  *var = value;
}