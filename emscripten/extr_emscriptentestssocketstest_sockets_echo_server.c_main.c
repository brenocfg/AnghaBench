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
struct sockaddr_in {int fd; int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  server_t ;
typedef  int /*<<< orphan*/  client_t ;
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
 struct sockaddr_in client ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int inet_pton (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int listen (int,int) ; 
 int /*<<< orphan*/  main_loop () ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 struct sockaddr_in server ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main() {

#ifdef _WIN32
  WSADATA wsaData = {};
  int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
  if (result) {
    printf("WSAStartup failed!\n");
    exit(1);
  }
#endif

  struct sockaddr_in addr;
  int res;

  atexit(cleanup);
  signal(SIGTERM, cleanup);

  memset(&server, 0, sizeof(server_t));
  memset(&client, 0, sizeof(client_t));

  // create the socket and set to non-blocking
#if !TEST_DGRAM
  server.fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
#else
  server.fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
#endif
  if (server.fd == -1) {
    perror("cannot create socket");
    exit(EXIT_FAILURE);
  }
#ifdef _WIN32
  unsigned long nonblocking = 1;
  ioctlsocket(server.fd, FIONBIO, &nonblocking);
#else
  fcntl(server.fd, F_SETFL, O_NONBLOCK);
#endif

  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(SOCKK);
  if (inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) != 1) {
    perror("inet_pton failed");
    exit(EXIT_FAILURE);
  }

  res = bind(server.fd, (struct sockaddr *)&addr, sizeof(addr));
  if (res == -1) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

#if !TEST_DGRAM
  res = listen(server.fd, 50);
  if (res == -1) {
    perror("listen failed");
    exit(EXIT_FAILURE);
  }
#endif

#ifdef __EMSCRIPTEN__
#if TEST_ASYNC
  // The first parameter being passed is actually an arbitrary userData pointer
  // for simplicity this test just passes a basic char*
  emscripten_set_socket_connection_callback("connection", async_main_loop);
  emscripten_set_socket_message_callback("message", async_main_loop);
  emscripten_set_socket_close_callback("close", async_main_loop);
#else
  emscripten_set_main_loop(main_loop, 60, 0);
#endif
#else
  while (1) main_loop();
#endif

  return EXIT_SUCCESS;
}