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
 int /*<<< orphan*/  isalnum (char) ; 

__attribute__((used)) static char *
ep_find_event_name_end (char *arg)
{
  char *s = arg;
  char *event_name_end = NULL;

  /* If we could depend upon the presense of strrpbrk, we'd use that... */
  if (arg == NULL)
    return NULL;

  /* We break out of the loop when we find a token delimiter.
     Basically, we're looking for alphanumerics and underscores;
     anything else delimites the token. */
  while (*s != '\0')
    {
      if (!isalnum (*s) && (*s != '_'))
	break;
      event_name_end = s;
      s++;
    }

  return event_name_end;
}