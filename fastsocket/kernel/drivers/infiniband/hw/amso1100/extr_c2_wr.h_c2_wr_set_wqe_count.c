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
typedef  int /*<<< orphan*/  u32 ;
struct c2wr_hdr {int /*<<< orphan*/  wqe_count; } ;

/* Variables and functions */

__attribute__((used)) static __inline__ void c2_wr_set_wqe_count(void *wr, u32 wqe_count)
{
	((struct c2wr_hdr *) wr)->wqe_count = wqe_count;
}