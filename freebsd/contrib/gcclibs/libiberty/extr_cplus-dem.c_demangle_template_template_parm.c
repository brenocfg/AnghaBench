#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct work_stuff {int dummy; } ;
struct TYPE_8__ {char* p; } ;
typedef  TYPE_1__ string ;

/* Variables and functions */
 int do_type (struct work_stuff*,char const**,TYPE_1__*) ; 
 scalar_t__ get_count (char const**,int*) ; 
 int /*<<< orphan*/  string_append (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  string_appends (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  string_delete (TYPE_1__*) ; 

__attribute__((used)) static int
demangle_template_template_parm (struct work_stuff *work,
                                 const char **mangled, string *tname)
{
  int i;
  int r;
  int need_comma = 0;
  int success = 1;
  string temp;

  string_append (tname, "template <");
  /* get size of template parameter list */
  if (get_count (mangled, &r))
    {
      for (i = 0; i < r; i++)
	{
	  if (need_comma)
	    {
	      string_append (tname, ", ");
	    }

	    /* Z for type parameters */
	    if (**mangled == 'Z')
	      {
		(*mangled)++;
		string_append (tname, "class");
	      }
	      /* z for template parameters */
	    else if (**mangled == 'z')
	      {
		(*mangled)++;
		success =
		  demangle_template_template_parm (work, mangled, tname);
		if (!success)
		  {
		    break;
		  }
	      }
	    else
	      {
		/* temp is initialized in do_type */
		success = do_type (work, mangled, &temp);
		if (success)
		  {
		    string_appends (tname, &temp);
		  }
		string_delete(&temp);
		if (!success)
		  {
		    break;
		  }
	      }
	  need_comma = 1;
	}

    }
  if (tname->p[-1] == '>')
    string_append (tname, " ");
  string_append (tname, "> class");
  return (success);
}