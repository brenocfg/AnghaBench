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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 scalar_t__ STATUS_CKSUM_LOOP ; 
 scalar_t__ qlcnic_get_sts_status (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int qlcnic_82xx_is_lb_pkt(u64 sts_data)
{
	return (qlcnic_get_sts_status(sts_data) == STATUS_CKSUM_LOOP) ? 1 : 0;
}