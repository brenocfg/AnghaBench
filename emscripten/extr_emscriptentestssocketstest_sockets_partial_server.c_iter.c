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

/* Variables and functions */
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cleanup_client () ; 
 int clientfd ; 
 int /*<<< orphan*/  do_send (int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int serverfd ; 

void iter() {
  int res;
  fd_set fdr;
  fd_set fdw;

  // see if there are any connections to accept / write to
  FD_ZERO(&fdr);
  FD_ZERO(&fdw);
  FD_SET(serverfd, &fdr);
  if (clientfd) FD_SET(clientfd, &fdw);
  res = select(64, &fdr, &fdw, NULL, NULL);
  if (res == -1) {
    perror("select failed");
    exit(EXIT_SUCCESS);
  }

  if (FD_ISSET(serverfd, &fdr)) {
    printf("accepted someone\n");
    clientfd = accept(serverfd, NULL, NULL);
    assert(clientfd != -1);
  }

  if (FD_ISSET(clientfd, &fdw)) {
    do_send(clientfd);
    cleanup_client();
  }
}