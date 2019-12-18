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
typedef  int /*<<< orphan*/  dmacHw_DESC_t ;
typedef  int /*<<< orphan*/  dmacHw_DESC_RING_t ;

/* Variables and functions */

uint32_t dmacHw_descriptorLen(uint32_t descCnt	/* [ IN ] Number of descriptor in the ring */
    ) {
	/* Need extra 4 byte to ensure 32 bit alignment  */
	return (descCnt * sizeof(dmacHw_DESC_t)) + sizeof(dmacHw_DESC_RING_t) +
		sizeof(uint32_t);
}