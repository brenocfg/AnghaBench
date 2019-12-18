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
 scalar_t__ taosReadSocket (int,char*,size_t) ; 

int taosReadMsg(int fd, void *buf, int nbytes) {
  int   nleft, nread;
  char *ptr = (char *)buf;

  nleft = nbytes;

  if (fd < 0) return -1;

  while (nleft > 0) {
    nread = (int)taosReadSocket(fd, ptr, (size_t)nleft);
    if (nread == 0) {
      break;
    } else if (nread < 0) {
      if (errno == EINTR) {
        continue;
      } else {
        return -1;
      }
    } else {
      nleft -= nread;
      ptr += nread;
    }
  }

  return (nbytes - nleft);
}