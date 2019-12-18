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
typedef  int bfd_signed_vma ;
typedef  scalar_t__ bfd_boolean ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  append_type (struct pr_handle*,char*) ; 
 char* pop_type (struct pr_handle*) ; 
 int /*<<< orphan*/  print_vma (int,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  substitute_type (struct pr_handle*,char*) ; 

__attribute__((used)) static bfd_boolean
pr_array_type (void *p, bfd_signed_vma lower, bfd_signed_vma upper,
	       bfd_boolean stringp)
{
  struct pr_handle *info = (struct pr_handle *) p;
  char *range_type;
  char abl[20], abu[20], ab[50];

  range_type = pop_type (info);
  if (range_type == NULL)
    return FALSE;

  if (lower == 0)
    {
      if (upper == -1)
	sprintf (ab, "|[]");
      else
	{
	  print_vma (upper + 1, abu, FALSE, FALSE);
	  sprintf (ab, "|[%s]", abu);
	}
    }
  else
    {
      print_vma (lower, abl, FALSE, FALSE);
      print_vma (upper, abu, FALSE, FALSE);
      sprintf (ab, "|[%s:%s]", abl, abu);
    }

  if (! substitute_type (info, ab))
    return FALSE;

  if (strcmp (range_type, "int") != 0)
    {
      if (! append_type (info, ":")
	  || ! append_type (info, range_type))
	return FALSE;
    }

  if (stringp)
    {
      if (! append_type (info, " /* string */"))
	return FALSE;
    }

  return TRUE;
}