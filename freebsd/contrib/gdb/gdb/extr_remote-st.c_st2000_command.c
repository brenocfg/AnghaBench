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
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  expect_prompt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_stdebug (char*,char*) ; 
 int /*<<< orphan*/  st2000_desc ; 

__attribute__((used)) static void
st2000_command (char *args, int fromtty)
{
  if (!st2000_desc)
    error ("st2000 target not open.");

  if (!args)
    error ("Missing command.");

  printf_stdebug ("%s\r", args);
  expect_prompt (0);
}