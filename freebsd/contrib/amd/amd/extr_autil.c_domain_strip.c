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
 scalar_t__ STREQ (char*,char*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static void
domain_strip(char *otherdom, char *localdom)
{
  char *p1, *p2;

  if ((p1 = strchr(otherdom, '.')) &&
      (p2 = strchr(localdom, '.')) &&
      STREQ(p1 + 1, p2 + 1))
    *p1 = '\0';
}