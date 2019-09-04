#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDLNet_Quit () ; 
 int /*<<< orphan*/  SDLNet_TCP_Close (scalar_t__) ; 
 int /*<<< orphan*/  exit (int) ; 
 TYPE_1__ state ; 

void finish(int result) {
  if (state.sd) {
    SDLNet_TCP_Close(state.sd);
    SDLNet_Quit();
  }
#ifdef __EMSCRIPTEN__
  REPORT_RESULT(result);
  emscripten_force_exit(result);
#else
  exit(result);
#endif
}