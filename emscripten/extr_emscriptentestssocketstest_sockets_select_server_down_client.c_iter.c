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
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 scalar_t__ FD_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int recv (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sockfd ; 

void iter() {
  static int retries = 0;

  fd_set sett;
  FD_ZERO(&sett);
  FD_SET(sockfd, &sett);
  
  // currently, we've connected to a closed server port.
  // the initial async connect "succeeded" and select
  // should say that the socket is ready for a non-blocking
  // read, however, the read should be 0 sized signalling
  // that the remote end has closed.
  int handles = select(64, &sett, NULL, NULL, NULL);
  if (handles == -1) {
    perror("select failed");
    finish(EXIT_FAILURE);
  }

  if (FD_ISSET(sockfd, &sett)) {
    char buffer[1024];
    int n = recv(sockfd, buffer, sizeof(buffer), 0);
    if (n == -1 && retries++ > 10) {
      perror("recv failed");
      finish(EXIT_FAILURE);
    } else if (!n) {
      perror("Connection to websocket server failed as expected.");
      finish(266);
    }
  }
}