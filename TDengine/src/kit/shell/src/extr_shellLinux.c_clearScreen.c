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
struct winsize {int ws_col; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOWN ; 
 int /*<<< orphan*/  LEFT ; 
 int /*<<< orphan*/  TIOCGWINSZ ; 
 int /*<<< orphan*/  UP ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct winsize*) ; 
 int /*<<< orphan*/  positionCursor (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

void clearScreen(int ecmd_pos, int cursor_pos) {
  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);

  int cursor_x = cursor_pos / w.ws_col;
  int cursor_y = cursor_pos % w.ws_col;
  int command_x = ecmd_pos / w.ws_col;
  positionCursor(cursor_y, LEFT);
  positionCursor(command_x - cursor_x, DOWN);
  fprintf(stdout, "\033[2K");
  for (int i = 0; i < command_x; i++) {
    positionCursor(1, UP);
    fprintf(stdout, "\033[2K");
  }
  fflush(stdout);
}