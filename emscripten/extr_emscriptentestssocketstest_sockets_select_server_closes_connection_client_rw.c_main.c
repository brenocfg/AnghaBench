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
struct sockaddr_in {int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; scalar_t__ length; int /*<<< orphan*/  buffer; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  msg_t ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ EINPROGRESS ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  MESSAGE ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCKK ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int connect (int,struct sockaddr*,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int inet_pton (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  main_loop () ; 
 int /*<<< orphan*/  malloc (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 struct sockaddr_in readmsg ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sockfd ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct sockaddr_in writemsg ; 

int main() {
  struct sockaddr_in addr;
  int res;

  memset(&readmsg, 0, sizeof(msg_t));
  memset(&writemsg, 0, sizeof(msg_t));
  writemsg.length = strlen(MESSAGE) + 1;
  writemsg.buffer = malloc(writemsg.length);
  strncpy(writemsg.buffer, MESSAGE, writemsg.length);

  sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sockfd == -1) {
    perror("cannot create socket");
    finish(EXIT_FAILURE);
  }
  fcntl(sockfd, F_SETFL, O_NONBLOCK);

  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(SOCKK);
  if (inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) != 1) {
    perror("inet_pton failed");
    finish(EXIT_FAILURE);
  }

  // This call should succeed (even if the server port is closed)
  res = connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));
  if (res == -1 && errno != EINPROGRESS) {
    perror("connect failed");
    finish(EXIT_FAILURE);
  }

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(main_loop, 0, 0);
#else
  while (1) main_loop();
#endif

  return EXIT_SUCCESS;
}