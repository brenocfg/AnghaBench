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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ isagain (int) ; 
 scalar_t__ recv (int,char*,size_t,int /*<<< orphan*/ ) ; 

ssize_t socket_receive_all_nonblocking(int fd, bool *error,
      void *data_, size_t size)
{
   const uint8_t *data = (const uint8_t*)data_;
   ssize_t         ret = recv(fd, (char*)data, size, 0);

   if (ret > 0)
      return ret;

   if (ret == 0)
   {
      /* Socket closed */
      *error = true;
      return -1;
   }

   if (isagain((int)ret))
      return 0;

   *error = true;
   return -1;
}