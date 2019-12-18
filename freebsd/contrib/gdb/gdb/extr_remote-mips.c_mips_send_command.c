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
 int /*<<< orphan*/  mips_desc ; 
 int /*<<< orphan*/  mips_expect (char const*) ; 
 char* mips_monitor_prompt ; 
 int /*<<< orphan*/  serial_write (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void
mips_send_command (const char *cmd, int prompt)
{
  serial_write (mips_desc, cmd, strlen (cmd));
  mips_expect (cmd);
  mips_expect ("\n");
  if (prompt)
    mips_expect (mips_monitor_prompt);
}