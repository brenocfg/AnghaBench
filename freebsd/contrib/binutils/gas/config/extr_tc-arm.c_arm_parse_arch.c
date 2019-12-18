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
struct arm_arch_option_table {int /*<<< orphan*/ * name; int /*<<< orphan*/  default_fpu; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 struct arm_arch_option_table* arm_archs ; 
 int arm_parse_extension (char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * march_cpu_opt ; 
 int /*<<< orphan*/ * march_fpu_opt ; 
 int /*<<< orphan*/  selected_cpu_name ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int
arm_parse_arch (char * str)
{
  const struct arm_arch_option_table *opt;
  char *ext = strchr (str, '+');
  int optlen;

  if (ext != NULL)
    optlen = ext - str;
  else
    optlen = strlen (str);

  if (optlen == 0)
    {
      as_bad (_("missing architecture name `%s'"), str);
      return 0;
    }

  for (opt = arm_archs; opt->name != NULL; opt++)
    if (strncmp (opt->name, str, optlen) == 0)
      {
	march_cpu_opt = &opt->value;
	march_fpu_opt = &opt->default_fpu;
	strcpy(selected_cpu_name, opt->name);

	if (ext != NULL)
	  return arm_parse_extension (ext, &march_cpu_opt);

	return 1;
      }

  as_bad (_("unknown architecture `%s'\n"), str);
  return 0;
}