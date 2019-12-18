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
struct type {int dummy; } ;

/* Variables and functions */
 char* TYPE_FN_FIELDLIST_NAME (struct type*,int) ; 
 scalar_t__ strchr (char*,char) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
is_type_conversion_operator (struct type *type, int i, int j)
{
  /* I think the whole idea of recognizing type conversion operators
     by their name is pretty terrible.  But I don't think our present
     data structure gives us any other way to tell.  If you know of
     some other way, feel free to rewrite this function.  */
  char *name = TYPE_FN_FIELDLIST_NAME (type, i);

  if (strncmp (name, "operator", 8) != 0)
    return 0;

  name += 8;
  if (! strchr (" \t\f\n\r", *name))
    return 0;

  while (strchr (" \t\f\n\r", *name))
    name++;

  if (!('a' <= *name && *name <= 'z')
      && !('A' <= *name && *name <= 'Z')
      && *name != '_')
    /* If this doesn't look like the start of an identifier, then it
       isn't a type conversion operator.  */
    return 0;
  else if (strncmp (name, "new", 3) == 0)
    name += 3;
  else if (strncmp (name, "delete", 6) == 0)
    name += 6;
  else
    /* If it doesn't look like new or delete, it's a type conversion
       operator.  */
    return 1;

  /* Is that really the end of the name?  */
  if (('a' <= *name && *name <= 'z')
      || ('A' <= *name && *name <= 'Z')
      || ('0' <= *name && *name <= '9')
      || *name == '_')
    /* No, so the identifier following "operator" must be a type name,
       and this is a type conversion operator.  */
    return 1;

  /* That was indeed the end of the name, so it was `operator new' or
     `operator delete', neither of which are type conversion operators.  */
  return 0;
}