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
struct pr_handle {int dummy; } ;
typedef  scalar_t__ bfd_signed_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  append_type (struct pr_handle*,char const*) ; 
 int /*<<< orphan*/  print_vma (scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_type (struct pr_handle*,char*) ; 

__attribute__((used)) static bfd_boolean
pr_enum_type (void *p, const char *tag, const char **names,
	      bfd_signed_vma *values)
{
  struct pr_handle *info = (struct pr_handle *) p;
  unsigned int i;
  bfd_signed_vma val;

  if (! push_type (info, "enum "))
    return FALSE;
  if (tag != NULL)
    {
      if (! append_type (info, tag)
	  || ! append_type (info, " "))
	return FALSE;
    }
  if (! append_type (info, "{ "))
    return FALSE;

  if (names == NULL)
    {
      if (! append_type (info, "/* undefined */"))
	return FALSE;
    }
  else
    {
      val = 0;
      for (i = 0; names[i] != NULL; i++)
	{
	  if (i > 0)
	    {
	      if (! append_type (info, ", "))
		return FALSE;
	    }

	  if (! append_type (info, names[i]))
	    return FALSE;

	  if (values[i] != val)
	    {
	      char ab[20];

	      print_vma (values[i], ab, FALSE, FALSE);
	      if (! append_type (info, " = ")
		  || ! append_type (info, ab))
		return FALSE;
	      val = values[i];
	    }

	  ++val;
	}
    }

  return append_type (info, " }");
}