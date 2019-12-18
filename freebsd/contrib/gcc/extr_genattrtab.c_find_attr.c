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
struct attr_desc {char const* name; struct attr_desc* next; scalar_t__ is_special; scalar_t__ is_const; scalar_t__ is_numeric; int /*<<< orphan*/ * default_val; int /*<<< orphan*/  first_value; } ;

/* Variables and functions */
 char* DEF_ATTR_STRING (char const*) ; 
 int MAX_ATTRS_INDEX ; 
 char const* alternative_name ; 
 struct attr_desc** attrs ; 
 struct attr_desc* oballoc (int) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

__attribute__((used)) static struct attr_desc *
find_attr (const char **name_p, int create)
{
  struct attr_desc *attr;
  int index;
  const char *name = *name_p;

  /* Before we resort to using `strcmp', see if the string address matches
     anywhere.  In most cases, it should have been canonicalized to do so.  */
  if (name == alternative_name)
    return NULL;

  index = name[0] & (MAX_ATTRS_INDEX - 1);
  for (attr = attrs[index]; attr; attr = attr->next)
    if (name == attr->name)
      return attr;

  /* Otherwise, do it the slow way.  */
  for (attr = attrs[index]; attr; attr = attr->next)
    if (name[0] == attr->name[0] && ! strcmp (name, attr->name))
      {
	*name_p = attr->name;
	return attr;
      }

  if (! create)
    return NULL;

  attr = oballoc (sizeof (struct attr_desc));
  attr->name = DEF_ATTR_STRING (name);
  attr->first_value = attr->default_val = NULL;
  attr->is_numeric = attr->is_const = attr->is_special = 0;
  attr->next = attrs[index];
  attrs[index] = attr;

  *name_p = attr->name;

  return attr;
}