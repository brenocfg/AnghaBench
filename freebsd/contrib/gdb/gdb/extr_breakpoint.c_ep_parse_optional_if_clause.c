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
 int /*<<< orphan*/  ep_skip_leading_whitespace (char**) ; 
 int /*<<< orphan*/  isspace (char) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static char *
ep_parse_optional_if_clause (char **arg)
{
  char *cond_string;

  if (((*arg)[0] != 'i') || ((*arg)[1] != 'f') || !isspace ((*arg)[2]))
    return NULL;

  /* Skip the "if" keyword. */
  (*arg) += 2;

  /* Skip any extra leading whitespace, and record the start of the
     condition string. */
  ep_skip_leading_whitespace (arg);
  cond_string = *arg;

  /* Assume that the condition occupies the remainder of the arg string. */
  (*arg) += strlen (cond_string);

  return cond_string;
}