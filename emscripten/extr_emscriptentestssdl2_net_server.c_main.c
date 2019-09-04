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
struct TYPE_2__ {int /*<<< orphan*/  sd; int /*<<< orphan*/  socketSet; int /*<<< orphan*/ ** clientSocket; } ;
typedef  int /*<<< orphan*/  IPaddress ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int MAX_CLIENTS ; 
 int /*<<< orphan*/  MAX_SOCKETS ; 
 int /*<<< orphan*/  SDLNet_AllocSocketSet (int /*<<< orphan*/ ) ; 
 char* SDLNet_GetError () ; 
 scalar_t__ SDLNet_Init () ; 
 scalar_t__ SDLNet_ResolveHost (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDLNet_TCP_AddSocket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDLNet_TCP_Open (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCKK ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  main_loop () ; 
 TYPE_1__ state ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv)
{
  IPaddress ip;

  if (SDLNet_Init() < 0)
  {
    fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
    exit(EXIT_FAILURE);
  }

  /* Resolving the host using NULL make network interface to listen */
  if (SDLNet_ResolveHost(&ip, INADDR_ANY, SOCKK) < 0)
  {
    fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
    exit(EXIT_FAILURE);
  }

  state.socketSet = SDLNet_AllocSocketSet(MAX_SOCKETS);

  for (int loop = 0; loop < MAX_CLIENTS; loop++)
  {
      state.clientSocket[loop] = NULL;
  }
  /* Open a connection with the IP provided (listen on the host's port) */
  if (!(state.sd = SDLNet_TCP_Open(&ip)))
  {
    fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
    exit(EXIT_FAILURE);
  }
  SDLNet_TCP_AddSocket(state.socketSet, state.sd);

  /* Wait for a connection, send data and term */
#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(main_loop, 60, 0);
#else
  while (1) main_loop();
#endif

  return EXIT_SUCCESS;
}