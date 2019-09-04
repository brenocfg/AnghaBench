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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  TYPE_1__* proc_t ;
struct TYPE_2__ {int /*<<< orphan*/  p_dispatchqueue_serialno_offset; } ;

/* Variables and functions */

uint64_t get_dispatchqueue_serialno_offset_from_proc(void *p)
{
	if(p != NULL) {
		proc_t pself = (proc_t)p;
		return (pself->p_dispatchqueue_serialno_offset);
	} else {
		return (uint64_t)0;
	}
}