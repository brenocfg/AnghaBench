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
struct arm_option_table {int* option; char* deprecated; int /*<<< orphan*/  value; int /*<<< orphan*/ * var; } ;
struct arm_long_option_table {int* option; char* deprecated; int (* func ) (int /*<<< orphan*/ ) ;} ;
struct arm_legacy_option_table {int* option; char* deprecated; int /*<<< orphan*/  value; int /*<<< orphan*/ ** var; } ;

/* Variables and functions */
#define  OPTION_EB 129 
#define  OPTION_EL 128 
 int /*<<< orphan*/  _ (char*) ; 
 struct arm_legacy_option_table* arm_legacy_opts ; 
 struct arm_long_option_table* arm_long_opts ; 
 struct arm_option_table* arm_opts ; 
 int /*<<< orphan*/  as_tsktsk (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  streq (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int*) ; 
 int /*<<< orphan*/  strncmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int target_big_endian ; 

int
md_parse_option (int c, char * arg)
{
  struct arm_option_table *opt;
  const struct arm_legacy_option_table *fopt;
  struct arm_long_option_table *lopt;

  switch (c)
    {
#ifdef OPTION_EB
    case OPTION_EB:
      target_big_endian = 1;
      break;
#endif

#ifdef OPTION_EL
    case OPTION_EL:
      target_big_endian = 0;
      break;
#endif

    case 'a':
      /* Listing option.  Just ignore these, we don't support additional
	 ones.	*/
      return 0;

    default:
      for (opt = arm_opts; opt->option != NULL; opt++)
	{
	  if (c == opt->option[0]
	      && ((arg == NULL && opt->option[1] == 0)
		  || streq (arg, opt->option + 1)))
	    {
#if WARN_DEPRECATED
	      /* If the option is deprecated, tell the user.  */
	      if (opt->deprecated != NULL)
		as_tsktsk (_("option `-%c%s' is deprecated: %s"), c,
			   arg ? arg : "", _(opt->deprecated));
#endif

	      if (opt->var != NULL)
		*opt->var = opt->value;

	      return 1;
	    }
	}

      for (fopt = arm_legacy_opts; fopt->option != NULL; fopt++)
	{
	  if (c == fopt->option[0]
	      && ((arg == NULL && fopt->option[1] == 0)
		  || streq (arg, fopt->option + 1)))
	    {
#if WARN_DEPRECATED
	      /* If the option is deprecated, tell the user.  */
	      if (fopt->deprecated != NULL)
		as_tsktsk (_("option `-%c%s' is deprecated: %s"), c,
			   arg ? arg : "", _(fopt->deprecated));
#endif

	      if (fopt->var != NULL)
		*fopt->var = &fopt->value;

	      return 1;
	    }
	}

      for (lopt = arm_long_opts; lopt->option != NULL; lopt++)
	{
	  /* These options are expected to have an argument.  */
	  if (c == lopt->option[0]
	      && arg != NULL
	      && strncmp (arg, lopt->option + 1,
			  strlen (lopt->option + 1)) == 0)
	    {
#if WARN_DEPRECATED
	      /* If the option is deprecated, tell the user.  */
	      if (lopt->deprecated != NULL)
		as_tsktsk (_("option `-%c%s' is deprecated: %s"), c, arg,
			   _(lopt->deprecated));
#endif

	      /* Call the sup-option parser.  */
	      return lopt->func (arg + strlen (lopt->option) - 1);
	    }
	}

      return 0;
    }

  return 1;
}