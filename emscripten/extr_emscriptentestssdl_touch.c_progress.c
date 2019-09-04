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
 int /*<<< orphan*/  got_down ; 
 int /*<<< orphan*/  got_move ; 
 int /*<<< orphan*/  got_up ; 
 int /*<<< orphan*/  printf (char*) ; 

void progress() {
  if (!got_down) printf("Hold down a finger to generate a touch down event.\n");
  else if (!got_move) printf("Drag a finger to generate a touch move event.\n");
  else if (!got_up) printf("Release a finger to generate a touch up event.\n");
  else
  {
#ifdef REPORT_RESULT
    REPORT_RESULT(0);
#endif
  }
}