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
struct termios {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oldtio ; 
 scalar_t__ tcgetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int get_old_terminal_mode(struct termios *tio) {
  /* Make sure stdin is a terminal. */
  if (!isatty(STDIN_FILENO)) {
    return -1;
  }

  // Get the parameter of current terminal
  if (tcgetattr(0, &oldtio) != 0) {
    return -1;
  }

  return 1;
}