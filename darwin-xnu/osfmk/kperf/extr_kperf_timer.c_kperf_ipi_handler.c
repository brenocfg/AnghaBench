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
struct kperf_timer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kperf_sample_cpu (struct kperf_timer*,int,int) ; 

void
kperf_ipi_handler(void *param)
{
	kperf_sample_cpu((struct kperf_timer *)param, false, false);
}