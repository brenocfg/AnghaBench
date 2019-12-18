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
struct TYPE_2__ {int size; char* mem; scalar_t__ pos; } ;

/* Variables and functions */
 TYPE_1__* file ; 

__attribute__((used)) static int mem_open(char * ogg, int size)
{
  static int one = 1;
  int n;
  if (one)
  {
    one = 0;
    for (n = 0; n < 4; n++)
      file[n].size = 0;
  }

  for (n = 0; n < 4; n++)
  {
    if (file[n].size == 0)
    {
      file[n].mem = ogg;
      file[n].size = size;
      file[n].pos = 0;
      return (0x666 + n);
    }
  }
  return -1;
}