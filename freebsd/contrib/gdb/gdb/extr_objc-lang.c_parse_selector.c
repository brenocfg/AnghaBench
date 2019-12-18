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
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ isalnum (char) ; 
 scalar_t__ isspace (char) ; 

char * 
parse_selector (char *method, char **selector)
{
  char *s1 = NULL;
  char *s2 = NULL;
  int found_quote = 0;

  char *nselector = NULL;

  gdb_assert (selector != NULL);

  s1 = method;

  while (isspace (*s1))
    s1++;
  if (*s1 == '\'') 
    {
      found_quote = 1;
      s1++;
    }
  while (isspace (*s1))
    s1++;
   
  nselector = s1;
  s2 = s1;

  for (;;) {
    if (isalnum (*s2) || (*s2 == '_') || (*s2 == ':'))
      *s1++ = *s2;
    else if (isspace (*s2))
      ;
    else if ((*s2 == '\0') || (*s2 == '\''))
      break;
    else
      return NULL;
    s2++;
  }
  *s1++ = '\0';

  while (isspace (*s2))
    s2++;
  if (found_quote)
    {
      if (*s2 == '\'') 
	s2++;
      while (isspace (*s2))
	s2++;
    }

  if (selector != NULL)
    *selector = nselector;

  return s2;
}