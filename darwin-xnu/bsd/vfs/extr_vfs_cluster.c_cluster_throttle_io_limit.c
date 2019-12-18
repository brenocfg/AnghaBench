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
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int THROTTLE_MAX_IOSIZE ; 
 scalar_t__ cluster_is_throttled (int /*<<< orphan*/ ) ; 

uint32_t
cluster_throttle_io_limit(vnode_t vp, uint32_t *limit)
{
	if (cluster_is_throttled(vp)) {
		*limit = THROTTLE_MAX_IOSIZE;
		return 1;
	}
	return 0;   
}