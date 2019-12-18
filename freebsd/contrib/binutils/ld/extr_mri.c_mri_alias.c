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
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  alias ; 
 int /*<<< orphan*/  mri_add_to_list (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 char* xstrdup (char*) ; 

void
mri_alias (const char *want, const char *is, int isn)
{
  if (!is)
    {
      char buf[20];

      /* Some sections are digits.  */
      sprintf (buf, "%d", isn);

      is = xstrdup (buf);

      if (is == NULL)
	abort ();
    }

  mri_add_to_list (&alias, is, 0, want, 0, 0);
}