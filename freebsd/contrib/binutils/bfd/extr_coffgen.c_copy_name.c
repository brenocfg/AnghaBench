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
typedef  scalar_t__ bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 char* bfd_alloc (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 

__attribute__((used)) static char *
copy_name (bfd *abfd, char *name, size_t maxlen)
{
  size_t len;
  char *newname;

  for (len = 0; len < maxlen; ++len)
    if (name[len] == '\0')
      break;

  if ((newname = bfd_alloc (abfd, (bfd_size_type) len + 1)) == NULL)
    return NULL;

  strncpy (newname, name, len);
  newname[len] = '\0';
  return newname;
}