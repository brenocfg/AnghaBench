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
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  ISALNUM (char) ; 
 char* bfd_alloc (int /*<<< orphan*/ *,int) ; 
 char* bfd_get_filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *
mangle_name (bfd *abfd, char *suffix)
{
  bfd_size_type size;
  char *buf;
  char *p;

  size = (strlen (bfd_get_filename (abfd))
	  + strlen (suffix)
	  + sizeof "_binary__");

  buf = bfd_alloc (abfd, size);
  if (buf == NULL)
    return "";

  sprintf (buf, "_binary_%s_%s", bfd_get_filename (abfd), suffix);

  /* Change any non-alphanumeric characters to underscores.  */
  for (p = buf; *p; p++)
    if (! ISALNUM (*p))
      *p = '_';

  return buf;
}