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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 int sendfile (int,int,int /*<<< orphan*/ *,size_t) ; 

ssize_t tsendfile(int dfd, int sfd, off_t *offset, size_t size) {
  size_t  leftbytes = size;
  ssize_t sentbytes;

  while (leftbytes > 0) {
    // TODO : Think to check if file is larger than 1GB
    if (leftbytes > 1000000000) leftbytes = 1000000000;
    sentbytes = sendfile(dfd, sfd, offset, leftbytes);
    if (sentbytes == -1) {
      if (errno == EINTR) {
        continue;
      }
      else {
        return -1;
      }
    }

    leftbytes -= sentbytes;
  }

  return size;
}