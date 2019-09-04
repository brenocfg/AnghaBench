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
 int /*<<< orphan*/  do_call (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * do_print ; 

int main(int argc, char **argv) {
  for (int i = 0; i < argc; i++) {
    do_call(i != 10 ? do_print : NULL, i != 15 ? "waka waka" : NULL);
  }
  return 0;
}