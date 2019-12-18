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
 char* _ (char*) ; 
 int /*<<< orphan*/  as_where (char**,unsigned int*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
identify (char *file)
{
  static int identified;

  if (identified)
    return;
  identified++;

  if (!file)
    {
      unsigned int x;
      as_where (&file, &x);
    }

  if (file)
    fprintf (stderr, "%s: ", file);
  fprintf (stderr, _("Assembler messages:\n"));
}