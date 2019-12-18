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
struct bts_tracer {int dummy; } ;
typedef  int /*<<< orphan*/  bts_ovfl_callback_t ;

/* Variables and functions */
 struct bts_tracer* ds_request_bts (int /*<<< orphan*/ *,int,void*,size_t,int /*<<< orphan*/ ,size_t,unsigned int) ; 

struct bts_tracer *ds_request_bts_cpu(int cpu, void *base, size_t size,
				      bts_ovfl_callback_t ovfl,
				      size_t th, unsigned int flags)
{
	return ds_request_bts(NULL, cpu, base, size, ovfl, th, flags);
}