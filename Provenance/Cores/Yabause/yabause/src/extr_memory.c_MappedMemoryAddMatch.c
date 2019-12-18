#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_3__ {size_t addr; size_t val; } ;
typedef  TYPE_1__ result_struct ;

/* Variables and functions */

__attribute__((used)) static int MappedMemoryAddMatch(u32 addr, u32 val, int searchtype, result_struct *result, u32 *numresults)
{
   result[numresults[0]].addr = addr;
   result[numresults[0]].val = val;
   numresults[0]++;
   return 0;
}