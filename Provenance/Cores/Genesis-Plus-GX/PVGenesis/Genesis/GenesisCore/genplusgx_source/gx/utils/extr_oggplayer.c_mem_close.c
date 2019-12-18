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
struct TYPE_2__ {scalar_t__ size; } ;

/* Variables and functions */
 int f_close (int*) ; 
 TYPE_1__* file ; 

__attribute__((used)) static int mem_close(int fd)
{
  if (fd >= 0x666 && fd <= 0x669) // it is a memory file descriptor?
  {
    fd -= 0x666;
    file[fd].size = 0;
    return 0;
  }
  else
    return f_close(&fd);
}