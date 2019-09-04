#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  state_t ;
struct TYPE_3__ {int /*<<< orphan*/  sd; int /*<<< orphan*/  msg_state; } ;
typedef  int /*<<< orphan*/  IPaddress ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  MSG_WRITE ; 
 char* SDLNet_GetError () ; 
 scalar_t__ SDLNet_Init () ; 
 scalar_t__ SDLNet_ResolveHost (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDLNet_TCP_Open (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCKK ; 
 int /*<<< orphan*/  finish (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  main_loop () ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ state ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv)
{
  IPaddress ip;   /* Server address */
  memset(&state, 0, sizeof(state_t));
  state.msg_state = MSG_WRITE;

  if (SDLNet_Init() < 0)
  {
    fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
    finish(EXIT_FAILURE);
  }

  /* Resolve the host we are connecting to */
  if (SDLNet_ResolveHost(&ip, "localhost", SOCKK) < 0)
  {
    fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
    finish(EXIT_FAILURE);
  }

  /* Open a connection with the IP provided */
  if (!(state.sd = SDLNet_TCP_Open(&ip)))
  {
    fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
    finish(EXIT_FAILURE);
  }

  /* Send messages */
#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(main_loop, 60, 0);
#else
  while (1) main_loop();
#endif

  return EXIT_SUCCESS;
}