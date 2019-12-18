#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int val; } ;
struct TYPE_4__ {TYPE_1__ slc0_token1; } ;

/* Variables and functions */
 int FIELD_TO_VALUE2 (int /*<<< orphan*/ ,int) ; 
 TYPE_2__ SLC ; 
 int /*<<< orphan*/  SLC_SLC0_TOKEN1_WDATA ; 
 int /*<<< orphan*/  SLC_SLC0_TOKEN1_WR ; 

__attribute__((used)) static inline void recv_size_reset(void)
{
    SLC.slc0_token1.val = FIELD_TO_VALUE2(SLC_SLC0_TOKEN1_WDATA, 0) | FIELD_TO_VALUE2(SLC_SLC0_TOKEN1_WR, 1);
}