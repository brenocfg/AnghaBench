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
 scalar_t__ IS_ABSOLUTE_PATH (char const*) ; 
 int /*<<< orphan*/  R_OK ; 
 int /*<<< orphan*/  access (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
if_exists_spec_function (int argc, const char **argv)
{
  /* Must have only one argument.  */
  if (argc == 1 && IS_ABSOLUTE_PATH (argv[0]) && ! access (argv[0], R_OK))
    return argv[0];

  return NULL;
}