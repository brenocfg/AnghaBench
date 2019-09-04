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
struct TYPE_2__ {int /*<<< orphan*/ ** clientSocket; int /*<<< orphan*/ * sd; } ;

/* Variables and functions */
 int MAX_CLIENTS ; 
 int /*<<< orphan*/  SDLNet_Quit () ; 
 int /*<<< orphan*/  SDLNet_TCP_Close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 TYPE_1__ state ; 

void finish() { // untested
  printf("Shutting down...\n");
  SDLNet_TCP_Close(state.sd);
  for (int loop = 0; loop < MAX_CLIENTS; loop++)
  {
    if (state.clientSocket[loop] != NULL)
    {
      SDLNet_TCP_Close(state.clientSocket[loop]);
      state.clientSocket[loop] = NULL;
    }
  }
  SDLNet_Quit();

#ifdef __EMSCRIPTEN__
  emscripten_force_exit(0);
#else
  exit(0);
#endif
}