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
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char const*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 char* xmalloc (scalar_t__) ; 

char *
concat (char const *s1, char const *s2, char const *s3)
{
  char *new = xmalloc (strlen (s1) + strlen (s2) + strlen (s3) + 1);
  sprintf (new, "%s%s%s", s1, s2, s3);
  return new;
}