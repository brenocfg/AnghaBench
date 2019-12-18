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
 char* bfd_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  stderr ; 

void
bfd_perror (const char *message)
{
  if (message == NULL || *message == '\0')
    fprintf (stderr, "%s\n", bfd_errmsg (bfd_get_error ()));
  else
    fprintf (stderr, "%s: %s\n", message, bfd_errmsg (bfd_get_error ()));
}