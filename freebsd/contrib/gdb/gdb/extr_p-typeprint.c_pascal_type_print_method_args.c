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
struct ui_file {int dummy; } ;

/* Variables and functions */
 int DEPRECATED_STREQN (char*,char*,int) ; 
 int /*<<< orphan*/  fputs_filtered (char*,struct ui_file*) ; 
 scalar_t__ isdigit (char) ; 
 int strtol (char*,char**,int /*<<< orphan*/ ) ; 

void
pascal_type_print_method_args (char *physname, char *methodname,
			       struct ui_file *stream)
{
  int is_constructor = DEPRECATED_STREQN (physname, "__ct__", 6);
  int is_destructor = DEPRECATED_STREQN (physname, "__dt__", 6);

  if (is_constructor || is_destructor)
    {
      physname += 6;
    }

  fputs_filtered (methodname, stream);

  if (physname && (*physname != 0))
    {
      int i = 0;
      int len = 0;
      char storec;
      char *argname;
      fputs_filtered (" (", stream);
      /* we must demangle this */
      while (isdigit (physname[0]))
	{
	  while (isdigit (physname[len]))
	    {
	      len++;
	    }
	  i = strtol (physname, &argname, 0);
	  physname += len;
	  storec = physname[i];
	  physname[i] = 0;
	  fputs_filtered (physname, stream);
	  physname[i] = storec;
	  physname += i;
	  if (physname[0] != 0)
	    {
	      fputs_filtered (", ", stream);
	    }
	}
      fputs_filtered (")", stream);
    }
}