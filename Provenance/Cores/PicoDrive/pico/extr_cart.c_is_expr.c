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
 char* sskip (char*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static int is_expr(const char *expr, char **pr)
{
  int len = strlen(expr);
  char *p = *pr;

  if (strncmp(expr, p, len) != 0)
    return 0;
  p = sskip(p + len);
  if (*p != '=')
    return 0; // wrong or malformed

  *pr = sskip(p + 1);
  return 1;
}