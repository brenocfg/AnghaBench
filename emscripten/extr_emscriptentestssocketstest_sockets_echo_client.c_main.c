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
struct sockaddr_in {int fd; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_family; scalar_t__ length; int /*<<< orphan*/  buffer; int /*<<< orphan*/  state; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  server_t ;
typedef  int /*<<< orphan*/  msg_t ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ EINPROGRESS ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 char* MESSAGE ; 
 int /*<<< orphan*/  MSG_WRITE ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  PF_INET ; 
 int SOCKK ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  assert (int) ; 
 int connect (int,struct sockaddr*,int) ; 
 struct sockaddr_in echo_msg ; 
 scalar_t__ echo_read ; 
 scalar_t__ echo_wrote ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish (int /*<<< orphan*/ ) ; 
 int getpeername (int,struct sockaddr*,int*) ; 
 int getsockname (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  htons (int) ; 
 char* inet_ntoa (int /*<<< orphan*/ ) ; 
 int inet_pton (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  main_loop () ; 
 int /*<<< orphan*/  malloc (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,scalar_t__,scalar_t__) ; 
 struct sockaddr_in server ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,scalar_t__) ; 

int main() {
  struct sockaddr_in addr;
  int res;

  memset(&server, 0, sizeof(server_t));
  server.state = MSG_WRITE;

  // setup the message we're going to echo
  memset(&echo_msg, 0, sizeof(msg_t));
  echo_msg.length = strlen(MESSAGE) + 1;
  echo_msg.buffer = malloc(echo_msg.length);
  strncpy(echo_msg.buffer, MESSAGE, echo_msg.length);

  echo_read = 0;
  echo_wrote = 0;

  // create the socket and set to non-blocking
#if !TEST_DGRAM
  server.fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
#else
  server.fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
#endif
  if (server.fd == -1) {
    perror("cannot create socket");
    finish(EXIT_FAILURE);
  }
  fcntl(server.fd, F_SETFL, O_NONBLOCK);

  // connect the socket
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(SOCKK);
  if (inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) != 1) {
    perror("inet_pton failed");
    finish(EXIT_FAILURE);
  }
  
  res = connect(server.fd, (struct sockaddr *)&addr, sizeof(addr));
  if (res == -1 && errno != EINPROGRESS) {
    perror("connect failed");
    finish(EXIT_FAILURE);
  }

  {
    int z;
    struct sockaddr_in adr_inet;
    socklen_t len_inet = sizeof adr_inet;
    z = getsockname(server.fd, (struct sockaddr *)&adr_inet, &len_inet);
    if (z != 0) {
      perror("getsockname");
      finish(EXIT_FAILURE);
    }
    char buffer[1000];
    sprintf(buffer, "%s:%u", inet_ntoa(adr_inet.sin_addr), (unsigned)ntohs(adr_inet.sin_port));
    // TODO: This is not the correct result: We should have a auto-bound address
    char *correct = "0.0.0.0:0";
    printf("got (expected) socket: %s (%s), size %lu (%lu)\n", buffer, correct, strlen(buffer), strlen(correct));
    assert(strlen(buffer) == strlen(correct));
    assert(strcmp(buffer, correct) == 0);
  }

  {
    int z;
    struct sockaddr_in adr_inet;
    socklen_t len_inet = sizeof adr_inet;
    z = getpeername(server.fd, (struct sockaddr *)&adr_inet, &len_inet);
    if (z != 0) {
      perror("getpeername");
      finish(EXIT_FAILURE);
    }
    char buffer[1000];
    sprintf(buffer, "%s:%u", inet_ntoa(adr_inet.sin_addr), (unsigned)ntohs(adr_inet.sin_port));
    char correct[1000];
    sprintf(correct, "127.0.0.1:%u", SOCKK);
    printf("got (expected) socket: %s (%s), size %lu (%lu)\n", buffer, correct, strlen(buffer), strlen(correct));
    assert(strlen(buffer) == strlen(correct));
    assert(strcmp(buffer, correct) == 0);
  }

#ifdef __EMSCRIPTEN__
#if TEST_ASYNC
  // The first parameter being passed is actually an arbitrary userData pointer
  // for simplicity this test just passes a basic char*
  emscripten_set_socket_error_callback("error", error_callback);
  emscripten_set_socket_open_callback("open", async_main_loop);
  emscripten_set_socket_message_callback("message", async_main_loop);
#else
  emscripten_set_main_loop(main_loop, 60, 0);
#endif
#else
  while (1) main_loop();
#endif

  return EXIT_SUCCESS;
}