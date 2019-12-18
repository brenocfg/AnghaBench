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
typedef  int uint32_t ;

/* Variables and functions */
 int THROUGHPUT_QOS_TIER_UNSPECIFIED ; 

uint32_t
qos_throughput_policy_package(uint32_t qv) {
	return (qv == THROUGHPUT_QOS_TIER_UNSPECIFIED) ? THROUGHPUT_QOS_TIER_UNSPECIFIED : ((0xFE << 16) | qv);
}