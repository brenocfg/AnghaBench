#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct work_stuff {int temp_start; int options; } ;
struct TYPE_13__ {int p; int b; } ;
typedef  TYPE_1__ string ;

/* Variables and functions */
 int DMGL_PARAMS ; 
 scalar_t__ HP_DEMANGLING ; 
 scalar_t__ arm_pt (struct work_stuff*,char const*,int,char const**,char const**) ; 
 char const* cplus_markers ; 
 int /*<<< orphan*/  do_hpacc_template_const_value (struct work_stuff*,char const**,TYPE_1__*) ; 
 int /*<<< orphan*/  do_hpacc_template_literal (struct work_stuff*,char const**,TYPE_1__*) ; 
 int /*<<< orphan*/  do_type (struct work_stuff*,char const**,TYPE_1__*) ; 
 int /*<<< orphan*/  snarf_numeric_literal (char const**,TYPE_1__*) ; 
 char* strchr (char const*,char const) ; 
 int /*<<< orphan*/  string_append (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  string_appendn (TYPE_1__*,char const*,int) ; 
 int /*<<< orphan*/  string_appends (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  string_delete (TYPE_1__*) ; 
 int /*<<< orphan*/  string_init (TYPE_1__*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static void
demangle_arm_hp_template (struct work_stuff *work, const char **mangled,
                          int n, string *declp)
{
  const char *p;
  const char *args;
  const char *e = *mangled + n;
  string arg;

  /* Check for HP aCC template spec: classXt1t2 where t1, t2 are
     template args */
  if (HP_DEMANGLING && ((*mangled)[n] == 'X'))
    {
      char *start_spec_args = NULL;
      int hold_options;

      /* First check for and omit template specialization pseudo-arguments,
         such as in "Spec<#1,#1.*>" */
      start_spec_args = strchr (*mangled, '<');
      if (start_spec_args && (start_spec_args - *mangled < n))
        string_appendn (declp, *mangled, start_spec_args - *mangled);
      else
        string_appendn (declp, *mangled, n);
      (*mangled) += n + 1;
      string_init (&arg);
      if (work->temp_start == -1) /* non-recursive call */
        work->temp_start = declp->p - declp->b;

      /* We want to unconditionally demangle parameter types in
	 template parameters.  */
      hold_options = work->options;
      work->options |= DMGL_PARAMS;

      string_append (declp, "<");
      while (1)
        {
          string_delete (&arg);
          switch (**mangled)
            {
              case 'T':
                /* 'T' signals a type parameter */
                (*mangled)++;
                if (!do_type (work, mangled, &arg))
                  goto hpacc_template_args_done;
                break;

              case 'U':
              case 'S':
                /* 'U' or 'S' signals an integral value */
                if (!do_hpacc_template_const_value (work, mangled, &arg))
                  goto hpacc_template_args_done;
                break;

              case 'A':
                /* 'A' signals a named constant expression (literal) */
                if (!do_hpacc_template_literal (work, mangled, &arg))
                  goto hpacc_template_args_done;
                break;

              default:
                /* Today, 1997-09-03, we have only the above types
                   of template parameters */
                /* FIXME: maybe this should fail and return null */
                goto hpacc_template_args_done;
            }
          string_appends (declp, &arg);
         /* Check if we're at the end of template args.
             0 if at end of static member of template class,
             _ if done with template args for a function */
          if ((**mangled == '\000') || (**mangled == '_'))
            break;
          else
            string_append (declp, ",");
        }
    hpacc_template_args_done:
      string_append (declp, ">");
      string_delete (&arg);
      if (**mangled == '_')
        (*mangled)++;
      work->options = hold_options;
      return;
    }
  /* ARM template? (Also handles HP cfront extensions) */
  else if (arm_pt (work, *mangled, n, &p, &args))
    {
      int hold_options;
      string type_str;

      string_init (&arg);
      string_appendn (declp, *mangled, p - *mangled);
      if (work->temp_start == -1)  /* non-recursive call */
	work->temp_start = declp->p - declp->b;

      /* We want to unconditionally demangle parameter types in
	 template parameters.  */
      hold_options = work->options;
      work->options |= DMGL_PARAMS;

      string_append (declp, "<");
      /* should do error checking here */
      while (args < e) {
	string_delete (&arg);

	/* Check for type or literal here */
	switch (*args)
	  {
	    /* HP cfront extensions to ARM for template args */
	    /* spec: Xt1Lv1 where t1 is a type, v1 is a literal value */
	    /* FIXME: We handle only numeric literals for HP cfront */
          case 'X':
            /* A typed constant value follows */
            args++;
            if (!do_type (work, &args, &type_str))
	      goto cfront_template_args_done;
            string_append (&arg, "(");
            string_appends (&arg, &type_str);
            string_delete (&type_str);
            string_append (&arg, ")");
            if (*args != 'L')
              goto cfront_template_args_done;
            args++;
            /* Now snarf a literal value following 'L' */
            if (!snarf_numeric_literal (&args, &arg))
	      goto cfront_template_args_done;
            break;

          case 'L':
            /* Snarf a literal following 'L' */
            args++;
            if (!snarf_numeric_literal (&args, &arg))
	      goto cfront_template_args_done;
            break;
          default:
            /* Not handling other HP cfront stuff */
            {
              const char* old_args = args;
              if (!do_type (work, &args, &arg))
                goto cfront_template_args_done;

              /* Fail if we didn't make any progress: prevent infinite loop. */
              if (args == old_args)
		{
		  work->options = hold_options;
		  return;
		}
            }
	  }
	string_appends (declp, &arg);
	string_append (declp, ",");
      }
    cfront_template_args_done:
      string_delete (&arg);
      if (args >= e)
	--declp->p; /* remove extra comma */
      string_append (declp, ">");
      work->options = hold_options;
    }
  else if (n>10 && strncmp (*mangled, "_GLOBAL_", 8) == 0
	   && (*mangled)[9] == 'N'
	   && (*mangled)[8] == (*mangled)[10]
	   && strchr (cplus_markers, (*mangled)[8]))
    {
      /* A member of the anonymous namespace.  */
      string_append (declp, "{anonymous}");
    }
  else
    {
      if (work->temp_start == -1) /* non-recursive call only */
	work->temp_start = 0;     /* disable in recursive calls */
      string_appendn (declp, *mangled, n);
    }
  *mangled += n;
}