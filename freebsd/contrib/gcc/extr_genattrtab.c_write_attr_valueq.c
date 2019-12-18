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
struct attr_desc {char const* name; scalar_t__ is_numeric; } ;

/* Variables and functions */
 int atoi (char const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  write_upcase (char const*) ; 

__attribute__((used)) static void
write_attr_valueq (struct attr_desc *attr, const char *s)
{
  if (attr->is_numeric)
    {
      int num = atoi (s);

      printf ("%d", num);

      if (num > 9 || num < 0)
	printf (" /* 0x%x */", num);
    }
  else
    {
      write_upcase (attr->name);
      printf ("_");
      write_upcase (s);
    }
}