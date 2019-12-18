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
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 
 char* xmalloc (size_t) ; 

__attribute__((used)) static char *
dupnstr (const char *s, size_t n)
{
  char *ret_val = xmalloc (n + 1);

  strncpy (ret_val, s, n);
  ret_val[n] = '\0';
  return ret_val;
}