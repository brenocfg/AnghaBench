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
struct arm_cpu_option_table {int /*<<< orphan*/ * name; scalar_t__ canonical_name; int /*<<< orphan*/  default_fpu; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 scalar_t__ TOUPPER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 struct arm_cpu_option_table* arm_cpus ; 
 int arm_parse_extension (char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * mcpu_cpu_opt ; 
 int /*<<< orphan*/ * mcpu_fpu_opt ; 
 scalar_t__* selected_cpu_name ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (scalar_t__*,scalar_t__) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int
arm_parse_cpu (char * str)
{
  const struct arm_cpu_option_table * opt;
  char * ext = strchr (str, '+');
  int optlen;

  if (ext != NULL)
    optlen = ext - str;
  else
    optlen = strlen (str);

  if (optlen == 0)
    {
      as_bad (_("missing cpu name `%s'"), str);
      return 0;
    }

  for (opt = arm_cpus; opt->name != NULL; opt++)
    if (strncmp (opt->name, str, optlen) == 0)
      {
	mcpu_cpu_opt = &opt->value;
	mcpu_fpu_opt = &opt->default_fpu;
	if (opt->canonical_name)
	  strcpy(selected_cpu_name, opt->canonical_name);
	else
	  {
	    int i;
	    for (i = 0; i < optlen; i++)
	      selected_cpu_name[i] = TOUPPER (opt->name[i]);
	    selected_cpu_name[i] = 0;
	  }

	if (ext != NULL)
	  return arm_parse_extension (ext, &mcpu_cpu_opt);

	return 1;
      }

  as_bad (_("unknown cpu `%s'"), str);
  return 0;
}