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
struct arm_option_cpu_value_table {int /*<<< orphan*/ * name; int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  arm_feature_set ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_MERGE_FEATURE_SETS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 struct arm_option_cpu_value_table* arm_extensions ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,...) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * xmalloc (int) ; 

__attribute__((used)) static int
arm_parse_extension (char * str, const arm_feature_set **opt_p)
{
  arm_feature_set *ext_set = xmalloc (sizeof (arm_feature_set));

  /* Copy the feature set, so that we can modify it.  */
  *ext_set = **opt_p;
  *opt_p = ext_set;

  while (str != NULL && *str != 0)
    {
      const struct arm_option_cpu_value_table * opt;
      char * ext;
      int optlen;

      if (*str != '+')
	{
	  as_bad (_("invalid architectural extension"));
	  return 0;
	}

      str++;
      ext = strchr (str, '+');

      if (ext != NULL)
	optlen = ext - str;
      else
	optlen = strlen (str);

      if (optlen == 0)
	{
	  as_bad (_("missing architectural extension"));
	  return 0;
	}

      for (opt = arm_extensions; opt->name != NULL; opt++)
	if (strncmp (opt->name, str, optlen) == 0)
	  {
	    ARM_MERGE_FEATURE_SETS (*ext_set, *ext_set, opt->value);
	    break;
	  }

      if (opt->name == NULL)
	{
	  as_bad (_("unknown architectural extnsion `%s'"), str);
	  return 0;
	}

      str = ext;
    };

  return 1;
}