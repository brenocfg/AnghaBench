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
typedef  int mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int clock_res_t ;
typedef  int clock_flavor_t ;
typedef  scalar_t__ clock_attr_t ;

/* Variables and functions */
#define  CLOCK_ALARM_CURRES 131 
#define  CLOCK_ALARM_MAXRES 130 
#define  CLOCK_ALARM_MINRES 129 
#define  CLOCK_GET_TIME_RES 128 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_INVALID_VALUE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int NSEC_PER_SEC ; 

kern_return_t
rtclock_getattr(
	clock_flavor_t			flavor,
	clock_attr_t			attr,		/* OUT */
	mach_msg_type_number_t	*count)		/* IN/OUT */
{
	if (*count != 1)
		return (KERN_FAILURE);

	switch (flavor) {

	case CLOCK_GET_TIME_RES:	/* >0 res */
	case CLOCK_ALARM_CURRES:	/* =0 no alarm */
	case CLOCK_ALARM_MINRES:
	case CLOCK_ALARM_MAXRES:
		*(clock_res_t *) attr = NSEC_PER_SEC / 100;
		break;

	default:
		return (KERN_INVALID_VALUE);
	}

	return (KERN_SUCCESS);
}