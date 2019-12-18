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
typedef  int /*<<< orphan*/  u8 ;
struct ring_descr {TYPE_1__* hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  rd_status; } ;

/* Variables and functions */

__attribute__((used)) static inline void rd_set_status(struct ring_descr *rd, u8 s)
{
	rd->hw->rd_status = s;	 /* may pass ownership to the hardware */
}