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
struct cmd_list_element {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * gnutarget ; 
 int /*<<< orphan*/ * gnutarget_string ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
set_gnutarget_command (char *ignore, int from_tty, struct cmd_list_element *c)
{
  if (strcmp (gnutarget_string, "auto") == 0)
    gnutarget = NULL;
  else
    gnutarget = gnutarget_string;
}