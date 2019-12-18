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
struct TYPE_4__ {TYPE_1__* save_area; } ;
struct TYPE_3__ {scalar_t__ esid; } ;

/* Variables and functions */
 TYPE_2__* get_slb_shadow () ; 

__attribute__((used)) static inline void slb_shadow_clear(unsigned long entry)
{
	get_slb_shadow()->save_area[entry].esid = 0;
}