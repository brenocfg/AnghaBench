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
 int /*<<< orphan*/  REGISTER_PREFIX ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
strip_reg_name (const char *name)
{
#ifdef REGISTER_PREFIX
  if (!strncmp (name, REGISTER_PREFIX, strlen (REGISTER_PREFIX)))
    name += strlen (REGISTER_PREFIX);
#endif
  if (name[0] == '%' || name[0] == '#')
    name++;
  return name;
}