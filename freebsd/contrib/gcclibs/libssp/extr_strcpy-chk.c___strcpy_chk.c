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
 int /*<<< orphan*/  __chk_fail () ; 
 char* memcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

char *
__strcpy_chk (char *__restrict__ dest, const char *__restrict__ src,
              size_t slen)
{
  size_t len = strlen (src);
  if (len >= slen)
    __chk_fail ();
  return memcpy (dest, src, len + 1);
}