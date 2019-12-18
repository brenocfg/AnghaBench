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
struct TYPE_2__ {scalar_t__ timeouts; scalar_t__ dmaErrors; scalar_t__ berrs; scalar_t__ irqs; scalar_t__ ioctls; scalar_t__ writes; scalar_t__ reads; } ;

/* Variables and functions */
 TYPE_1__ statistics ; 

__attribute__((used)) static void reset_counters(void)
{
        statistics.reads = 0;
        statistics.writes = 0;
        statistics.ioctls = 0;
        statistics.irqs = 0;
        statistics.berrs = 0;
        statistics.dmaErrors = 0;
        statistics.timeouts = 0;
}