#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  port; } ;
typedef  int /*<<< orphan*/  ENetPeer ;
typedef  TYPE_1__ ENetAddress ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int /*<<< orphan*/  SOCKK ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enet_address_set_host (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  enet_deinitialize ; 
 int /*<<< orphan*/ * enet_host_connect (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * enet_host_create (int /*<<< orphan*/ *,int,int,int,int) ; 
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

  printf("creating host\n");

  host = enet_host_create (NULL /* create a client host */,
                              1 /* only allow 1 outgoing connection */,
                              2 /* allow up 2 channels to be used, 0 and 1 */,
                              57600 / 8 /* 56K modem with 56 Kbps downstream bandwidth */,
                              14400 / 8 /* 56K modem with 14 Kbps upstream bandwidth */);
  if (host == NULL)
  {
    fprintf (stderr,
              "An error occurred while trying to create an ENet client host.\n");
    exit (EXIT_FAILURE);
  }

  ENetAddress address;
  enet_address_set_host (& address, "localhost");
  address.port = SOCKK;

  printf("connecting to server...\n");

  ENetPeer *peer = enet_host_connect (host, & address, 2, 0);

  if (peer == NULL)
  {
    fprintf (stderr,
    "No available peers for initiating an ENet connection.\n");
    exit (EXIT_FAILURE);
  }

#ifdef __EMSCRIPTEN__
#if USE_IFRAME
  emscripten_run_script("console.log('adding iframe');"
                        "var iframe = document.createElement('iframe');"
                        "iframe.src = 'server.html';"
                        "iframe.width = '100%';"
                        "iframe.height = '33%';"
                        "document.body.appendChild(iframe);"
                        "console.log('added.');");
#endif
#endif

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(main_loop, 3, 1);
#else
  while (1) main_loop();
#endif

  return 1;
}