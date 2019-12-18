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
 int /*<<< orphan*/  memcpy (char*,char const*,unsigned long) ; 
 scalar_t__ xmalloc (unsigned long) ; 

__attribute__((used)) static char *
savestring (const char *start, unsigned long len)
{
  char *ret;

  ret = (char *) xmalloc (len + 1);
  memcpy (ret, start, len);
  ret[len] = '\0';
  return ret;
}