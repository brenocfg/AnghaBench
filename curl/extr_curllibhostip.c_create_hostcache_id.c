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
 scalar_t__ TOLOWER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msnprintf (char*,int,char*,int) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void
create_hostcache_id(const char *name, int port, char *ptr, size_t buflen)
{
  size_t len = strlen(name);
  if(len > (buflen - 7))
    len = buflen - 7;
  /* store and lower case the name */
  while(len--)
    *ptr++ = (char)TOLOWER(*name++);
  msnprintf(ptr, 7, ":%u", port);
}