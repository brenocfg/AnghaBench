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
 scalar_t__ EINPROGRESS ; 
 int EXIT_FAILURE ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCKK ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int connect (int,struct sockaddr*,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish (int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int inet_pton (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iter () ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sockfd ; 

int main() {
  struct sockaddr_in addr;
  int res;

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
  emscripten_set_main_loop(iter, 0, 0);
#else
  while (1) iter();
#endif
  
  return EXIT_FAILURE;
}