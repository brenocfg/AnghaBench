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
 int /*<<< orphan*/  GO_USAGE ; 
 int /*<<< orphan*/  jump_command (char*,int) ; 
 int /*<<< orphan*/  printf_filtered (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tbreak_command (char*,int) ; 

__attribute__((used)) static void
go_command (char *line_no, int from_tty)
{
  if (line_no == (char *) NULL || !*line_no)
    printf_filtered (GO_USAGE);
  else
    {
      tbreak_command (line_no, from_tty);
      jump_command (line_no, from_tty);
    }
}