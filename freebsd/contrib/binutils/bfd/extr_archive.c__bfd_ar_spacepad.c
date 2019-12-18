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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  memset (char*,char,size_t) ; 
 int /*<<< orphan*/  snprintf (char*,int,char const*,long) ; 
 size_t strlen (char*) ; 

void
_bfd_ar_spacepad (char *p, size_t n, const char *fmt, long val)
{
  static char buf[20];
  size_t len;
  snprintf (buf, sizeof (buf), fmt, val);
  len = strlen (buf);
  if (len < n)
    {
      memcpy (p, buf, len);
      memset (p + len, ' ', n - len);
    }
  else
    memcpy (p, buf, n);
}