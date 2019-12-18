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
struct TYPE_2__ {scalar_t__ size; scalar_t__ pos; int mem; } ;

/* Variables and functions */
 TYPE_1__* file ; 
 int /*<<< orphan*/  memcpy (void*,int,int) ; 
 int read (int,char*,int) ; 

__attribute__((used)) static int f_read(void * punt, int bytes, int blocks, int *f)
{
  int b;
  int c;
  int d;

  if (bytes * blocks <= 0)
    return 0;

  blocks = bytes * blocks;
  c = 0;

  while (blocks > 0)
  {
    b = blocks;
    if (b > 4096)
      b = 4096;

    if (*f >= 0x666 && *f <= 0x669)
    {
      d = (*f) - 0x666;
      if (file[d].size == 0)
        return -1;
      if ((file[d].pos + b) > file[d].size)
        b = file[d].size - file[d].pos;
      if (b > 0)
      {
        memcpy(punt, file[d].mem + file[d].pos, b);
        file[d].pos += b;
      }
    }
    else
      b = read(*f, ((char *) punt) + c, b);

    if (b <= 0)
    {
      return c / bytes;
    }
    c += b;
    blocks -= b;
  }
  return c / bytes;
}