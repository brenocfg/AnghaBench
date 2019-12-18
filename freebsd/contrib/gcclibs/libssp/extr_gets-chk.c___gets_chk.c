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
 scalar_t__ INT_MAX ; 
 int /*<<< orphan*/  __chk_fail () ; 
 char* alloca (size_t) ; 
 char* fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* gets (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  stdin ; 
 size_t strlen (char*) ; 

char *
__gets_chk (char *s, size_t slen)
{
  char *ret, *buf;

  if (slen >= (size_t) INT_MAX)
    return gets (s);

  if (slen <= 8192)
    buf = alloca (slen + 1);
  else
    buf = malloc (slen + 1);
  if (buf == NULL)
    return gets (s);

  ret = fgets (buf, (int) (slen + 1), stdin);
  if (ret != NULL)
    {
      size_t len = strlen (buf);
      if (len > 0 && buf[len - 1] == '\n')
        --len;
      if (len == slen)
        __chk_fail ();
      memcpy (s, buf, len);
      s[len] = '\0';
      ret = s;
    }

  if (slen > 8192)
    free (buf);
  return ret;
}