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
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  pError (char*,int,...) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ taosReadSocket (int,char*,size_t) ; 

int taosReadn(int fd, char *ptr, int nbytes) {
  int nread, nready, nleft = nbytes;

  fd_set         fset;
  struct timeval tv;

  while (nleft > 0) {
    tv.tv_sec = 30;
    tv.tv_usec = 0;
    FD_ZERO(&fset);
    FD_SET(fd, &fset);
    if ((nready = select(fd + 1, NULL, &fset, NULL, &tv)) == 0) {
      errno = ETIMEDOUT;
      pError("fd %d timeout\n", fd);
      break;
    } else if (nready < 0) {
      if (errno == EINTR) continue;
      pError("select error, %d (%s)", errno, strerror(errno));
      return -1;
    }

    if ((nread = (int)taosReadSocket(fd, ptr, (size_t)nleft)) < 0) {
      if (errno == EINTR) continue;
      pError("read error, %d (%s)", errno, strerror(errno));
      return -1;

    } else if (nread == 0) {
      pError("fd %d EOF", fd);
      break;  // EOF
    }

    nleft -= nread;
    ptr += nread;
  }

  return (nbytes - nleft);
}