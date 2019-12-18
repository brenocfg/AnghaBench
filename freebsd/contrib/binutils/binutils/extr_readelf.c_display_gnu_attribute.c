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

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 
 int read_uleb128 (unsigned char*,unsigned int*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static unsigned char *
display_gnu_attribute (unsigned char *p,
		       unsigned char *(*display_proc_gnu_attribute)
			    (unsigned char *, int))
{
  int tag;
  unsigned int len;
  int val;
  int type;

  tag = read_uleb128 (p, &len);
  p += len;

  /* Tag_compatibility is the only generic GNU attribute defined at
     present.  */
  if (tag == 32)
    {
      val = read_uleb128 (p, &len);
      p += len;
      printf ("flag = %d, vendor = %s\n", val, p);
      p += strlen((char *)p) + 1;
      return p;
    }

  if ((tag & 2) == 0 && display_proc_gnu_attribute)
    return display_proc_gnu_attribute (p, tag);

  if (tag & 1)
    type = 1; /* String.  */
  else
    type = 2; /* uleb128.  */
  printf ("  Tag_unknown_%d: ", tag);

  if (type == 1)
    {
      printf ("\"%s\"\n", p);
      p += strlen ((char *)p) + 1;
    }
  else
    {
      val = read_uleb128 (p, &len);
      p += len;
      printf ("%d (0x%x)\n", val, val);
    }

  return p;
}