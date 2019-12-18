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

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 scalar_t__ taosWriteSocket (int,char*,size_t) ; 

int taosWriteMsg(int fd, void *buf, int nbytes) {
  int   nleft, nwritten;
  char *ptr = (char *)buf;

  nleft = nbytes;

  while (nleft > 0) {
    nwritten = (int)taosWriteSocket(fd, (char *)ptr, (size_t)nleft);
    if (nwritten <= 0) {
      if (errno == EINTR)
        continue;
      else
        return -1;
    } else {
      nleft -= nwritten;
      ptr += nwritten;
    }
  }

  return (nbytes - nleft);
}