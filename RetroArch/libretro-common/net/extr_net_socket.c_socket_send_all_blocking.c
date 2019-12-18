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
 int /*<<< orphan*/  MSG_NOSIGNAL ; 
 scalar_t__ isagain (int) ; 
 scalar_t__ send (int,char const*,size_t,int /*<<< orphan*/ ) ; 

int socket_send_all_blocking(int fd, const void *data_, size_t size,
      bool no_signal)
{
   const uint8_t *data = (const uint8_t*)data_;

   while (size)
   {
      ssize_t ret = send(fd, (const char*)data, size,
            no_signal ? MSG_NOSIGNAL : 0);
      if (ret <= 0)
      {
         if (isagain((int)ret))
            continue;

         return false;
      }

      data += ret;
      size -= ret;
   }

   return true;
}