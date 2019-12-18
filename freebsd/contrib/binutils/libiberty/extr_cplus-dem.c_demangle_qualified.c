#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct work_stuff {int constructor; int destructor; int numk; char** ktypevec; } ;
struct TYPE_17__ {int /*<<< orphan*/  b; } ;
typedef  TYPE_1__ string ;

/* Variables and functions */
 scalar_t__ EDG_DEMANGLING ; 
 int /*<<< orphan*/  LEN_STRING (TYPE_1__*) ; 
 char* SCOPE_STRING (struct work_stuff*) ; 
 int /*<<< orphan*/  STRING_EMPTY (TYPE_1__*) ; 
 int atoi (char*) ; 
 int consume_count (char const**) ; 
 int consume_count_with_underscores (char const**) ; 
 int demangle_template (struct work_stuff*,char const**,TYPE_1__*,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int do_type (struct work_stuff*,char const**,TYPE_1__*) ; 
 int /*<<< orphan*/  recursively_demangle (struct work_stuff*,char const**,TYPE_1__*,int) ; 
 int register_Btype (struct work_stuff*) ; 
 int /*<<< orphan*/  remember_Btype (struct work_stuff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  remember_Ktype (struct work_stuff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_append (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  string_appends (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  string_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  string_delete (TYPE_1__*) ; 
 int /*<<< orphan*/  string_init (TYPE_1__*) ; 
 int /*<<< orphan*/  string_prepends (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static int
demangle_qualified (struct work_stuff *work, const char **mangled,
                    string *result, int isfuncname, int append)
{
  int qualifiers = 0;
  int success = 1;
  char num[2];
  string temp;
  string last_name;
  int bindex = register_Btype (work);

  /* We only make use of ISFUNCNAME if the entity is a constructor or
     destructor.  */
  isfuncname = (isfuncname
		&& ((work->constructor & 1) || (work->destructor & 1)));

  string_init (&temp);
  string_init (&last_name);

  if ((*mangled)[0] == 'K')
    {
    /* Squangling qualified name reuse */
      int idx;
      (*mangled)++;
      idx = consume_count_with_underscores (mangled);
      if (idx == -1 || idx >= work -> numk)
        success = 0;
      else
        string_append (&temp, work -> ktypevec[idx]);
    }
  else
    switch ((*mangled)[1])
    {
    case '_':
      /* GNU mangled name with more than 9 classes.  The count is preceded
	 by an underscore (to distinguish it from the <= 9 case) and followed
	 by an underscore.  */
      (*mangled)++;
      qualifiers = consume_count_with_underscores (mangled);
      if (qualifiers == -1)
	success = 0;
      break;

    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      /* The count is in a single digit.  */
      num[0] = (*mangled)[1];
      num[1] = '\0';
      qualifiers = atoi (num);

      /* If there is an underscore after the digit, skip it.  This is
	 said to be for ARM-qualified names, but the ARM makes no
	 mention of such an underscore.  Perhaps cfront uses one.  */
      if ((*mangled)[2] == '_')
	{
	  (*mangled)++;
	}
      (*mangled) += 2;
      break;

    case '0':
    default:
      success = 0;
    }

  if (!success)
    return success;

  /* Pick off the names and collect them in the temp buffer in the order
     in which they are found, separated by '::'.  */

  while (qualifiers-- > 0)
    {
      int remember_K = 1;
      string_clear (&last_name);

      if (*mangled[0] == '_')
	(*mangled)++;

      if (*mangled[0] == 't')
	{
	  /* Here we always append to TEMP since we will want to use
	     the template name without the template parameters as a
	     constructor or destructor name.  The appropriate
	     (parameter-less) value is returned by demangle_template
	     in LAST_NAME.  We do not remember the template type here,
	     in order to match the G++ mangling algorithm.  */
	  success = demangle_template(work, mangled, &temp,
				      &last_name, 1, 0);
	  if (!success)
	    break;
	}
      else if (*mangled[0] == 'K')
	{
          int idx;
          (*mangled)++;
          idx = consume_count_with_underscores (mangled);
          if (idx == -1 || idx >= work->numk)
            success = 0;
          else
            string_append (&temp, work->ktypevec[idx]);
          remember_K = 0;

	  if (!success) break;
	}
      else
	{
	  if (EDG_DEMANGLING)
            {
	      int namelength;
 	      /* Now recursively demangle the qualifier
 	       * This is necessary to deal with templates in
 	       * mangling styles like EDG */
	      namelength = consume_count (mangled);
	      if (namelength == -1)
		{
		  success = 0;
		  break;
		}
 	      recursively_demangle(work, mangled, &temp, namelength);
            }
          else
            {
              string_delete (&last_name);
              success = do_type (work, mangled, &last_name);
              if (!success)
                break;
              string_appends (&temp, &last_name);
            }
	}

      if (remember_K)
	remember_Ktype (work, temp.b, LEN_STRING (&temp));

      if (qualifiers > 0)
	string_append (&temp, SCOPE_STRING (work));
    }

  remember_Btype (work, temp.b, LEN_STRING (&temp), bindex);

  /* If we are using the result as a function name, we need to append
     the appropriate '::' separated constructor or destructor name.
     We do this here because this is the most convenient place, where
     we already have a pointer to the name and the length of the name.  */

  if (isfuncname)
    {
      string_append (&temp, SCOPE_STRING (work));
      if (work -> destructor & 1)
	string_append (&temp, "~");
      string_appends (&temp, &last_name);
    }

  /* Now either prepend the temp buffer to the result, or append it,
     depending upon the state of the append flag.  */

  if (append)
    string_appends (result, &temp);
  else
    {
      if (!STRING_EMPTY (result))
	string_append (&temp, SCOPE_STRING (work));
      string_prepends (result, &temp);
    }

  string_delete (&last_name);
  string_delete (&temp);
  return (success);
}