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
typedef  int thread_qos_t ;

/* Variables and functions */
#define  THREAD_QOS_MAINTENANCE 128 

__attribute__((used)) static inline int
_wq_bucket(thread_qos_t qos)
{
	// Map both BG and MT to the same bucket by over-shifting down and
	// clamping MT and BG together.
	switch (qos) {
	case THREAD_QOS_MAINTENANCE:
		return 0;
	default:
		return qos - 2;
	}
}