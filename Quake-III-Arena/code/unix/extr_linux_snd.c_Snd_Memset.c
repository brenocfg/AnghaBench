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
 int /*<<< orphan*/  Com_Memset (void*,int const,size_t const) ; 
 int /*<<< orphan*/  use_custom_memset ; 

void Snd_Memset (void* dest, const int val, const size_t count)
{
  int *pDest;
  int i, iterate;

  if (!use_custom_memset)
  {
    Com_Memset(dest,val,count);
    return;
  }
  iterate = count / sizeof(int);
  pDest = (int*)dest;
  for(i=0; i<iterate; i++)
  {
    pDest[i] = val;
  }
}