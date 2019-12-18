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
 scalar_t__ bfd_alloc (int /*<<< orphan*/ *,int) ; 
 char* memcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 

char *
_bfd_elf_attr_strdup (bfd *abfd, const char * s)
{
  char * p;
  int len;
  
  len = strlen (s) + 1;
  p = (char *) bfd_alloc (abfd, len);
  return memcpy (p, s, len);
}