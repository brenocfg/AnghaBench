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
typedef  scalar_t__ ogg_int64_t ;
struct TYPE_2__ {scalar_t__ size; scalar_t__ pos; } ;

/* Variables and functions */
 TYPE_1__* file ; 
 int lseek (int,int,int) ; 

__attribute__((used)) static int f_seek(int *f, ogg_int64_t offset, int mode)
{
  if(f==NULL) return(-1);

  int k, d;
  mode &= 3;
  if (*f >= 0x666 && *f <= 0x669)
  {
    d = (*f) - 0x666;
    k = 0;

    if (file[d].size == 0)
      return -1;

    if (mode == 0)
    {
      if ((offset) >= file[d].size)
      {
        file[d].pos = file[d].size;
        k = -1;
      }
      else if ((offset) < 0)
      {
        file[d].pos = 0;
        k = -1;
      }
      else
        file[d].pos = offset;
    }
    if (mode == 1)
    {
      if ((file[d].pos + offset) >= file[d].size)
      {
        file[d].pos = file[d].size;
        k = -1;
      }
      else if ((file[d].pos + offset) < 0)
      {
        file[d].pos = 0;
        k = -1;
      }
      else
        file[d].pos += offset;
    }
    if (mode == 2)
    {

      if ((file[d].size + offset) >= file[d].size)
      {
        file[d].pos = file[d].size;
        k = -1;
      }
      else if ((file[d].size + offset) < 0)
      {
        file[d].pos = 0;
        k = -1;
      }
      else
        file[d].pos = file[d].size + offset;
    }

  }
  else
    k = lseek(*f, (int) offset, mode);

  if (k < 0)
    k = -1;
  else
    k = 0;
  return k;
}