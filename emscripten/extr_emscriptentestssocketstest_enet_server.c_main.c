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
struct TYPE_3__ {int /*<<< orphan*/  port; int /*<<< orphan*/  host; } ;
typedef  TYPE_1__ ENetAddress ;

/* Variables and functions */
 int /*<<< orphan*/  ENET_HOST_ANY ; 
 int EXIT_FAILURE ; 
 int /*<<< orphan*/  SOCKK ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enet_deinitialize ; 
 int /*<<< orphan*/ * enet_host_create (TYPE_1__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ enet_initialize () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * host ; 
 int /*<<< orphan*/  main_loop () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stderr ; 

int main (int argc, char ** argv)
{
  if (enet_initialize () != 0)
  {
    fprintf (stderr, "An error occurred while initializing ENet.\n");
    return EXIT_FAILURE;
  }
  atexit (enet_deinitialize);

  ENetAddress address;
  address.host = ENET_HOST_ANY;
  address.port = SOCKK;
  printf("create!\n");
  host = enet_host_create (& address /* the address to bind the server host to */,
                             32 /* allow up to 32 clients and/or outgoing connections */,
                             2 /* allow up to 2 channels to be used, 0 and 1 */,
                             0 /* assume any amount of incoming bandwidth */,
                             0 /* assume any amount of outgoing bandwidth */);
  if (host == NULL)
  {
    fprintf (stderr,
    "An error occurred while trying to create an ENet server host.\n");
    exit (EXIT_FAILURE);
  }

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(main_loop, 3, 1);
#else
  while (1) main_loop();
#endif

  return 1;
}