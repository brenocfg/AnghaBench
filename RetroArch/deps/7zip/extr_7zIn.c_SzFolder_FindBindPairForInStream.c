#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_5__ {size_t NumBindPairs; TYPE_1__* BindPairs; } ;
struct TYPE_4__ {size_t InIndex; } ;
typedef  TYPE_2__ CSzFolder ;

/* Variables and functions */

int SzFolder_FindBindPairForInStream(CSzFolder *p, uint32_t inStreamIndex)
{
   uint32_t i;
   for (i = 0; i < p->NumBindPairs; i++)
      if (p->BindPairs[i].InIndex == inStreamIndex)
         return i;
   return -1;
}