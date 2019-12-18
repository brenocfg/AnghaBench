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
 int DOWN ; 
 int LEFT ; 
 int RIGHT ; 
 int UP ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stdout ; 

void positionCursor(int step, int direction) {
  if (step > 0) {
    if (direction == LEFT) {
      fprintf(stdout, "\033[%dD", step);
    } else if (direction == RIGHT) {
      fprintf(stdout, "\033[%dC", step);
    } else if (direction == UP) {
      fprintf(stdout, "\033[%dA", step);
    } else if (direction == DOWN) {
      fprintf(stdout, "\033[%dB", step);
    }
    fflush(stdout);
  }
}