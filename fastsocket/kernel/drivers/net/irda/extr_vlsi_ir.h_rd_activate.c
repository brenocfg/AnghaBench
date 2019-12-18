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
struct ring_descr {TYPE_1__* hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  rd_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  RD_ACTIVE ; 

__attribute__((used)) static inline void rd_activate(struct ring_descr *rd)
{
	rd->hw->rd_status |= RD_ACTIVE;
}