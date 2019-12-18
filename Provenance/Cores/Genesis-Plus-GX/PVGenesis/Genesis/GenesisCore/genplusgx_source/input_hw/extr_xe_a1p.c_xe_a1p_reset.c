#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int** analog; } ;
struct TYPE_3__ {int State; scalar_t__ Latency; scalar_t__ Counter; } ;

/* Variables and functions */
 TYPE_2__ input ; 
 TYPE_1__* xe_a1p ; 

void xe_a1p_reset(int index)
{
  input.analog[index][0] = 128;
  input.analog[index][1] = 128;
  input.analog[index+1][0] = 128;
  index >>= 2;
  xe_a1p[index].State = 0x40;
  xe_a1p[index].Counter = 0;
  xe_a1p[index].Latency = 0;
}