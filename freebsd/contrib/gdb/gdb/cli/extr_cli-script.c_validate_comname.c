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
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/  error_no_arg (char*) ; 
 int /*<<< orphan*/  isalnum (char) ; 

__attribute__((used)) static void
validate_comname (char *comname)
{
  char *p;

  if (comname == 0)
    error_no_arg ("name of command to define");

  p = comname;
  while (*p)
    {
      if (!isalnum (*p) && *p != '-' && *p != '_')
	error ("Junk in argument list: \"%s\"", p);
      p++;
    }
}