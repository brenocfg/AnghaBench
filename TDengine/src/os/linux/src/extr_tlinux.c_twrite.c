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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 scalar_t__ write (int,void*,size_t) ; 

ssize_t twrite(int fd, void *buf, size_t n) {
  size_t nleft = n; 
  ssize_t nwritten = 0;
  char *tbuf = (char *)buf;

  while (nleft > 0) {
    nwritten = write(fd, (void *)tbuf, nleft);
    if (nwritten < 0) {
      if (errno == EINTR) {
        continue;
      }
      return -1;
    }
    nleft -= nwritten;
    tbuf += nwritten;
  }

  return n;
}