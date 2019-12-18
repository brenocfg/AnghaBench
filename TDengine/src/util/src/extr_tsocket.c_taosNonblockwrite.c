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
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSG_NOSIGNAL ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  pError (char*,int,...) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 scalar_t__ send (int,char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosSetNonblocking (int,int) ; 

int taosNonblockwrite(int fd, char *ptr, int nbytes) {
  taosSetNonblocking(fd, 1);

  int            nleft, nwritten, nready;
  fd_set         fset;
  struct timeval tv;

  nleft = nbytes;
  while (nleft > 0) {
    tv.tv_sec = 30;
    tv.tv_usec = 0;
    FD_ZERO(&fset);
    FD_SET(fd, &fset);
    if ((nready = select(fd + 1, NULL, &fset, NULL, &tv)) == 0) {
      errno = ETIMEDOUT;
      pError("fd %d timeout, no enough space to write", fd);
      break;

    } else if (nready < 0) {
      if (errno == EINTR) continue;

      pError("select error, %d (%s)", errno, strerror(errno));
      return -1;
    }

    nwritten = (int)send(fd, ptr, (size_t)nleft, MSG_NOSIGNAL);
    if (nwritten <= 0) {
      if (errno == EAGAIN || errno == EINTR) continue;

      pError("write error, %d (%s)", errno, strerror(errno));
      return -1;
    }

    nleft -= nwritten;
    ptr += nwritten;
  }

  taosSetNonblocking(fd, 0);

  return (nbytes - nleft);
}