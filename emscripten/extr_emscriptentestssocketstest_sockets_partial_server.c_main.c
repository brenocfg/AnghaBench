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
struct sockaddr_in {int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SOCKK ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  cleanup ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int inet_pton (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iter () ; 
 int listen (int,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int serverfd ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main() {
  struct sockaddr_in addr;
  int res;

  atexit(cleanup);
  signal(SIGTERM, cleanup);

  // create the socket
  serverfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (serverfd == -1) {
    perror("cannot create socket");
    exit(EXIT_FAILURE);
  }
  fcntl(serverfd, F_SETFL, O_NONBLOCK);

  // bind and listen to the supplied port
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(SOCKK);
  if (inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) != 1) {
    perror("inet_pton failed");
    exit(EXIT_FAILURE);
  }

  res = bind(serverfd, (struct sockaddr *)&addr, sizeof(addr));
  if (res == -1) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  res = listen(serverfd, 50);
  if (res == -1) {
    perror("listen failed");
    exit(EXIT_FAILURE);
  }

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(iter, 60, 0);
#else
  while (1) iter();
#endif

  return EXIT_SUCCESS;
}