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
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmp_prefix ; 

__attribute__((used)) static char *
dlltmp (char **buf, const char *fmt)
{
  if (!*buf)
    {
      *buf = malloc (strlen (tmp_prefix) + 64);
      sprintf (*buf, fmt, tmp_prefix);
    }
  return *buf;
}