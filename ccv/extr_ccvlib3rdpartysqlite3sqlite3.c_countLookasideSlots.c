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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {struct TYPE_3__* pNext; } ;
typedef  TYPE_1__ LookasideSlot ;

/* Variables and functions */

__attribute__((used)) static u32 countLookasideSlots(LookasideSlot *p){
  u32 cnt = 0;
  while( p ){
    p = p->pNext;
    cnt++;
  }
  return cnt;
}