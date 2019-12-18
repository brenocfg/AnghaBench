#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  section_htab; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  abort () ; 
 char* bfd_malloc (unsigned int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,unsigned int) ; 
 scalar_t__ section_hash_lookup (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 unsigned int strlen (char const*) ; 

char *
bfd_get_unique_section_name (bfd *abfd, const char *templat, int *count)
{
  int num;
  unsigned int len;
  char *sname;

  len = strlen (templat);
  sname = bfd_malloc (len + 8);
  if (sname == NULL)
    return NULL;
  memcpy (sname, templat, len);
  num = 1;
  if (count != NULL)
    num = *count;

  do
    {
      /* If we have a million sections, something is badly wrong.  */
      if (num > 999999)
	abort ();
      sprintf (sname + len, ".%d", num++);
    }
  while (section_hash_lookup (&abfd->section_htab, sname, FALSE, FALSE));

  if (count != NULL)
    *count = num;
  return sname;
}