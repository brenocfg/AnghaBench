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
struct TYPE_5__ {size_t NumCoders; TYPE_1__* Coders; } ;
struct TYPE_4__ {scalar_t__ NumOutStreams; } ;
typedef  TYPE_2__ CSzFolder ;

/* Variables and functions */

uint32_t SzFolder_GetNumOutStreams(CSzFolder *p)
{
   uint32_t result = 0;
   uint32_t i;
   for (i = 0; i < p->NumCoders; i++)
      result += p->Coders[i].NumOutStreams;
   return result;
}