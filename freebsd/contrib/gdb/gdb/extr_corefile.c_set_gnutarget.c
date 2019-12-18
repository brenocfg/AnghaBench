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
 int /*<<< orphan*/ * gnutarget_string ; 
 int /*<<< orphan*/ * savestring (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gnutarget_command (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ *) ; 

void
set_gnutarget (char *newtarget)
{
  if (gnutarget_string != NULL)
    xfree (gnutarget_string);
  gnutarget_string = savestring (newtarget, strlen (newtarget));
  set_gnutarget_command (NULL, 0, NULL);
}