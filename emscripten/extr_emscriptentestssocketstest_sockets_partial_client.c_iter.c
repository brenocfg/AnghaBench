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
 scalar_t__ EAGAIN ; 
 scalar_t__ EWOULDBLOCK ; 
 int EXIT_FAILURE ; 
 int /*<<< orphan*/  FD_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  finish (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int recv (int /*<<< orphan*/ ,char*,char,int /*<<< orphan*/ ) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sockfd ; 
 int /*<<< orphan*/  stderr ; 
 int sum ; 

void iter() {
  char buffer[1024];
  char packetLength;
  fd_set fdr;
  int i;
  int res;

  // make sure that sockfd is ready to read
  FD_ZERO(&fdr);
  FD_SET(sockfd, &fdr);
  res = select(64, &fdr, NULL, NULL, NULL);
  if (res == -1) {
    perror("select failed");
    finish(EXIT_FAILURE);
  } else if (!FD_ISSET(sockfd, &fdr)) {
    return;
  }

  res = recv(sockfd, buffer, 1, 0);
  if (res == -1) {
    if (errno == EAGAIN || errno == EWOULDBLOCK) {
      return; //try again
    }

    perror("unexcepted end of data");
    finish(EXIT_FAILURE);
  }

  if (res != 1) {
    fprintf(stderr, "should read 1 byte, got: %d, sum %d so far\n", res, sum);
    finish(EXIT_FAILURE);
  }

  packetLength = buffer[0];
  res = recv(sockfd, buffer, packetLength, 0);

  printf("got %d,%d\n", res, packetLength);

  if (res != packetLength) {
    fprintf(stderr, "lost packet data, expected: %d readed: %d", packetLength, res);
    finish(EXIT_FAILURE);
  }

  for (i = 0; i < packetLength; ++i) {
    if (buffer[i] != i+1) {
      fprintf(stderr, "packet corrupted, expected: %d, actual: %d", i+1, buffer[i]);
      finish(EXIT_FAILURE);
    }

    sum += buffer[i];
  }

  if (packetLength == buffer[0]) { // \x01\x01 - end marker
    printf("sum: %d\n", sum);
    finish(sum);
  }
}