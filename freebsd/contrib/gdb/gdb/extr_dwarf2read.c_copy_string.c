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
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* xmalloc (int) ; 

__attribute__((used)) static char *
copy_string (const char *buf, int len)
{
  char *s = xmalloc (len + 1);
  memcpy (s, buf, len);
  s[len] = '\0';

  return s;
}