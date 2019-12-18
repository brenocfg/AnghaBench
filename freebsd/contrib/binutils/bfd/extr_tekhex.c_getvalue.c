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
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ISHEX (char) ; 
 int /*<<< orphan*/  TRUE ; 
 int hex_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
getvalue (char **srcp, bfd_vma *valuep)
{
  char *src = *srcp;
  bfd_vma value = 0;
  unsigned int len;

  if (!ISHEX (*src))
    return FALSE;

  len = hex_value (*src++);
  if (len == 0)
    len = 16;
  while (len--)
    {
      if (!ISHEX (*src))
	return FALSE;
      value = value << 4 | hex_value (*src++);
    }

  *srcp = src;
  *valuep = value;
  return TRUE;
}