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
struct TYPE_2__ {int pos; } ;

/* Variables and functions */
 TYPE_1__* file ; 
 int lseek (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static long f_tell(int *f)
{
  int k, d;

  if (*f >= 0x666 && *f <= 0x669)
  {
    d = (*f) - 0x666;
    k = file[d].pos;
  }
  else
    k = lseek(*f, 0, 1);

  return (long) k;
}