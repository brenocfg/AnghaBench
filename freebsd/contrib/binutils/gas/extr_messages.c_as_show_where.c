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
 int /*<<< orphan*/  as_where (char**,unsigned int*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,unsigned int) ; 
 int /*<<< orphan*/  identify (char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
as_show_where (void)
{
  char *file;
  unsigned int line;

  as_where (&file, &line);
  identify (file);
  if (file)
    fprintf (stderr, "%s:%u: ", file, line);
}