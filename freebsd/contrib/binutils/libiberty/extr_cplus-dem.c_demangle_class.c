#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct work_stuff {int constructor; int destructor; int temp_start; } ;
struct TYPE_10__ {char* p; char* b; } ;
typedef  TYPE_1__ string ;

/* Variables and functions */
 int /*<<< orphan*/  LEN_STRING (TYPE_1__*) ; 
 char* SCOPE_STRING (struct work_stuff*) ; 
 scalar_t__ demangle_class_name (struct work_stuff*,char const**,TYPE_1__*) ; 
 int register_Btype (struct work_stuff*) ; 
 int /*<<< orphan*/  remember_Btype (struct work_stuff*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  remember_Ktype (struct work_stuff*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_delete (TYPE_1__*) ; 
 int /*<<< orphan*/  string_init (TYPE_1__*) ; 
 int /*<<< orphan*/  string_prepend (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  string_prepends (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static int
demangle_class (struct work_stuff *work, const char **mangled, string *declp)
{
  int success = 0;
  int btype;
  string class_name;
  char *save_class_name_end = 0;

  string_init (&class_name);
  btype = register_Btype (work);
  if (demangle_class_name (work, mangled, &class_name))
    {
      save_class_name_end = class_name.p;
      if ((work->constructor & 1) || (work->destructor & 1))
	{
          /* adjust so we don't include template args */
          if (work->temp_start && (work->temp_start != -1))
            {
              class_name.p = class_name.b + work->temp_start;
            }
	  string_prepends (declp, &class_name);
	  if (work -> destructor & 1)
	    {
	      string_prepend (declp, "~");
              work -> destructor -= 1;
	    }
	  else
	    {
	      work -> constructor -= 1;
	    }
	}
      class_name.p = save_class_name_end;
      remember_Ktype (work, class_name.b, LEN_STRING(&class_name));
      remember_Btype (work, class_name.b, LEN_STRING(&class_name), btype);
      string_prepend (declp, SCOPE_STRING (work));
      string_prepends (declp, &class_name);
      success = 1;
    }
  string_delete (&class_name);
  return (success);
}