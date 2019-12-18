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
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  printf_unfiltered (char*,char) ; 
 scalar_t__ serial_write (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ sr_get_debug () ; 
 int /*<<< orphan*/  sr_get_desc () ; 

void
sr_write (char *a, int l)
{
  int i;

  if (serial_write (sr_get_desc (), a, l) != 0)
    perror_with_name ("sr_write: Error writing to remote");

  if (sr_get_debug () > 0)
    for (i = 0; i < l; i++)
      printf_unfiltered ("%c", a[i]);

  return;
}