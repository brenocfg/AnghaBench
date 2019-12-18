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
 int /*<<< orphan*/  set_binding_values (char const*,char const**,int /*<<< orphan*/ *) ; 

char *
BINDTEXTDOMAIN (const char *domainname, const char *dirname)
{
  set_binding_values (domainname, &dirname, NULL);
  return (char *) dirname;
}