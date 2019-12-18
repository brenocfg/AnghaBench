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

/* Variables and functions */
 int DisaWord (unsigned int) ; 

__attribute__((used)) static unsigned int DisaLong(unsigned int a)
{
  unsigned int d=0;
  if (DisaWord==NULL) return d;

  d= DisaWord(a)<<16;
  d|=DisaWord(a+2)&0xffff;
  return d;
}