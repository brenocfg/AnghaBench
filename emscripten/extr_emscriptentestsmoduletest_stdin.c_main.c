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
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  main_loop () ; 
 int /*<<< orphan*/  sleep (int) ; 

int main(int argc, char const *argv[])
{
  fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);

  // SM shell doesn't implement an event loop and therefor doesn't support
  // emscripten_set_main_loop. However, its stdin reads are sync so it
  // should exit out after calling main_loop once.
  main_loop();

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(main_loop, 60, 0);
#else
  while (1) main_loop(); sleep(1);
#endif
  return 0;
}