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
struct mt_cpu {int dummy; } ;
struct TYPE_2__ {struct mt_cpu cpu_monotonic; } ;

/* Variables and functions */
 TYPE_1__* current_cpu_datap () ; 

struct mt_cpu *
mt_cur_cpu(void)
{
	return &current_cpu_datap()->cpu_monotonic;
}