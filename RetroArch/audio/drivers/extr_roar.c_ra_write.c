#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
struct TYPE_2__ {scalar_t__ nonblocking; int /*<<< orphan*/  vss; } ;
typedef  TYPE_1__ roar_t ;

/* Variables and functions */
 scalar_t__ roar_vs_write (int /*<<< orphan*/ ,char const*,size_t,int*) ; 

__attribute__((used)) static ssize_t ra_write(void *data, const void *buf, size_t size)
{
   int err;
   size_t written = 0;
   roar_t   *roar = (roar_t*)data;

   if (size == 0)
      return 0;

   while (written < size)
   {
      ssize_t rc;
      size_t write_amt = size - written;

      if ((rc = roar_vs_write(roar->vss,
                  (const char*)buf + written, write_amt, &err)) < (ssize_t)write_amt)
      {
         if (roar->nonblocking)
            return rc;
         else if (rc < 0)
            return -1;
      }
      written += rc;
   }

   return size;
}