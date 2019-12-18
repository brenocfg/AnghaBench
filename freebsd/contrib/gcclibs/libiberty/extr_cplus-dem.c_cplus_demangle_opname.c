#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  work ;
struct work_stuff {int options; } ;
struct TYPE_6__ {scalar_t__ b; scalar_t__ p; } ;
typedef  TYPE_1__ string ;
struct TYPE_7__ {char const* in; char* out; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_3__*) ; 
 scalar_t__ ISLOWER (unsigned char) ; 
 int /*<<< orphan*/  cplus_markers ; 
 scalar_t__ do_type (struct work_stuff*,char const**,TYPE_1__*) ; 
 scalar_t__ memcmp (char const*,char const*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* optable ; 
 int /*<<< orphan*/  squangle_mop_up (struct work_stuff*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/ * strchr (int /*<<< orphan*/ ,char const) ; 
 int /*<<< orphan*/  string_delete (TYPE_1__*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncat (char*,scalar_t__,scalar_t__) ; 

int
cplus_demangle_opname (const char *opname, char *result, int options)
{
  int len, len1, ret;
  string type;
  struct work_stuff work[1];
  const char *tem;

  len = strlen(opname);
  result[0] = '\0';
  ret = 0;
  memset ((char *) work, 0, sizeof (work));
  work->options = options;

  if (opname[0] == '_' && opname[1] == '_'
      && opname[2] == 'o' && opname[3] == 'p')
    {
      /* ANSI.  */
      /* type conversion operator.  */
      tem = opname + 4;
      if (do_type (work, &tem, &type))
	{
	  strcat (result, "operator ");
	  strncat (result, type.b, type.p - type.b);
	  string_delete (&type);
	  ret = 1;
	}
    }
  else if (opname[0] == '_' && opname[1] == '_'
	   && ISLOWER((unsigned char)opname[2])
	   && ISLOWER((unsigned char)opname[3]))
    {
      if (opname[4] == '\0')
	{
	  /* Operator.  */
	  size_t i;
	  for (i = 0; i < ARRAY_SIZE (optable); i++)
	    {
	      if (strlen (optable[i].in) == 2
		  && memcmp (optable[i].in, opname + 2, 2) == 0)
		{
		  strcat (result, "operator");
		  strcat (result, optable[i].out);
		  ret = 1;
		  break;
		}
	    }
	}
      else
	{
	  if (opname[2] == 'a' && opname[5] == '\0')
	    {
	      /* Assignment.  */
	      size_t i;
	      for (i = 0; i < ARRAY_SIZE (optable); i++)
		{
		  if (strlen (optable[i].in) == 3
		      && memcmp (optable[i].in, opname + 2, 3) == 0)
		    {
		      strcat (result, "operator");
		      strcat (result, optable[i].out);
		      ret = 1;
		      break;
		    }
		}
	    }
	}
    }
  else if (len >= 3
	   && opname[0] == 'o'
	   && opname[1] == 'p'
	   && strchr (cplus_markers, opname[2]) != NULL)
    {
      /* see if it's an assignment expression */
      if (len >= 10 /* op$assign_ */
	  && memcmp (opname + 3, "assign_", 7) == 0)
	{
	  size_t i;
	  for (i = 0; i < ARRAY_SIZE (optable); i++)
	    {
	      len1 = len - 10;
	      if ((int) strlen (optable[i].in) == len1
		  && memcmp (optable[i].in, opname + 10, len1) == 0)
		{
		  strcat (result, "operator");
		  strcat (result, optable[i].out);
		  strcat (result, "=");
		  ret = 1;
		  break;
		}
	    }
	}
      else
	{
	  size_t i;
	  for (i = 0; i < ARRAY_SIZE (optable); i++)
	    {
	      len1 = len - 3;
	      if ((int) strlen (optable[i].in) == len1
		  && memcmp (optable[i].in, opname + 3, len1) == 0)
		{
		  strcat (result, "operator");
		  strcat (result, optable[i].out);
		  ret = 1;
		  break;
		}
	    }
	}
    }
  else if (len >= 5 && memcmp (opname, "type", 4) == 0
	   && strchr (cplus_markers, opname[4]) != NULL)
    {
      /* type conversion operator */
      tem = opname + 5;
      if (do_type (work, &tem, &type))
	{
	  strcat (result, "operator ");
	  strncat (result, type.b, type.p - type.b);
	  string_delete (&type);
	  ret = 1;
	}
    }
  squangle_mop_up (work);
  return ret;

}