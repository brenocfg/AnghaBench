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
typedef  void* uint64_t ;
struct TYPE_2__ {void* scan_interval; void* scan_limit; } ;

/* Variables and functions */
 int KERN_INVALID_ARGUMENT ; 
 int KERN_SUCCESS ; 
#define  SCAN_INTERVAL 130 
#define  SCAN_LIMIT 129 
#define  THRESHOLD 128 
 int /*<<< orphan*/  master_cpu ; 
 int /*<<< orphan*/  timer_call_cpu (int /*<<< orphan*/ ,void (*) (void*),void*) ; 
 TYPE_1__ timer_longterm ; 
 int /*<<< orphan*/  timer_sysctl_set_threshold ; 

int
timer_sysctl_set(int oid, uint64_t value)
{
	switch (oid) {
	case THRESHOLD:
		timer_call_cpu(
			master_cpu,
			(void (*)(void *)) timer_sysctl_set_threshold,
			(void *) value);
		return KERN_SUCCESS;
	case SCAN_LIMIT:
		timer_longterm.scan_limit = value;
		return KERN_SUCCESS;
	case SCAN_INTERVAL:
		timer_longterm.scan_interval = value;
		return KERN_SUCCESS;
	default:
		return KERN_INVALID_ARGUMENT;
	}
}