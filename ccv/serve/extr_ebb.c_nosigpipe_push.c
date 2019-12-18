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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int MSG_NOSIGNAL ; 
 int /*<<< orphan*/  send (int,void const*,size_t,int) ; 

__attribute__((used)) static ssize_t 
nosigpipe_push(int fd, const void *buf, size_t len)
{
  int flags = 0;
#ifdef MSG_NOSIGNAL
  flags = MSG_NOSIGNAL;
#endif
  return send(fd, buf, len, flags);
}