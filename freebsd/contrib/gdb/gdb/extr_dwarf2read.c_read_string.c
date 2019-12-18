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
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int HOST_CHAR_BIT ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *
read_string (bfd *abfd, char *buf, unsigned int *bytes_read_ptr)
{
  /* If the size of a host char is 8 bits, we can return a pointer
     to the string, otherwise we have to copy the string to a buffer
     allocated on the temporary obstack.  */
  gdb_assert (HOST_CHAR_BIT == 8);
  if (*buf == '\0')
    {
      *bytes_read_ptr = 1;
      return NULL;
    }
  *bytes_read_ptr = strlen (buf) + 1;
  return buf;
}