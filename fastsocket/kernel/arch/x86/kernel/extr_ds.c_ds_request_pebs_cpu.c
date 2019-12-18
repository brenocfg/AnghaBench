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
struct pebs_tracer {int dummy; } ;
typedef  int /*<<< orphan*/  pebs_ovfl_callback_t ;

/* Variables and functions */
 struct pebs_tracer* ds_request_pebs (int /*<<< orphan*/ *,int,void*,size_t,int /*<<< orphan*/ ,size_t,unsigned int) ; 

struct pebs_tracer *ds_request_pebs_cpu(int cpu, void *base, size_t size,
					pebs_ovfl_callback_t ovfl,
					size_t th, unsigned int flags)
{
	return ds_request_pebs(NULL, cpu, base, size, ovfl, th, flags);
}