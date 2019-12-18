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
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tty_Hide () ; 
 int /*<<< orphan*/  tty_Show () ; 
 scalar_t__ ttycon_on ; 

void  Sys_Print( const char *msg )
{
  if (ttycon_on)
  {
    tty_Hide();
  }
  fputs(msg, stderr);
  if (ttycon_on)
  {
    tty_Show();
  }
}