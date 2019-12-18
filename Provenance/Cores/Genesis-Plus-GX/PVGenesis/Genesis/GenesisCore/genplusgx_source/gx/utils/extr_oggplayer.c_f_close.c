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
struct TYPE_2__ {void* mem; scalar_t__ pos; scalar_t__ size; } ;

/* Variables and functions */
 int close (int) ; 
 TYPE_1__* file ; 

__attribute__((used)) static int f_close(int *f)
{
  int d;
  if (*f >= 0x666 && *f <= 0x669)
  {
    d = (*f) - 0x666;
    file[d].size = 0;
    file[d].pos = 0;
    if (file[d].mem)
    {
      file[d].mem = (void *) 0;
    }
    return 0;
  }
  else
    return close(*f);
  return 0;
}