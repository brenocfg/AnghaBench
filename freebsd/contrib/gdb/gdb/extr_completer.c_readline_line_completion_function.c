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
 char* line_completion_function (char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rl_line_buffer ; 
 int /*<<< orphan*/  rl_point ; 

char *
readline_line_completion_function (const char *text, int matches)
{
  return line_completion_function (text, matches, rl_line_buffer, rl_point);
}