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
typedef  int /*<<< orphan*/  sysv_zone_t ;
struct buffer_head {int b_size; scalar_t__ b_data; } ;

/* Variables and functions */

__attribute__((used)) static inline sysv_zone_t *block_end(struct buffer_head *bh)
{
	return (sysv_zone_t*)((char*)bh->b_data + bh->b_size);
}