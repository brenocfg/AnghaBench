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
typedef  int /*<<< orphan*/  alpha ;

/* Variables and functions */
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static char *
prefix_encode (char *start, unsigned code)
{
  static char alpha[26] = "abcdefghijklmnopqrstuvwxyz";
  static char buf[32];
  char *p;
  strcpy (buf, start);
  p = strchr (buf, '\0');
  do
    *p++ = alpha[code % sizeof (alpha)];
  while ((code /= sizeof (alpha)) != 0);
  *p = '\0';
  return buf;
}