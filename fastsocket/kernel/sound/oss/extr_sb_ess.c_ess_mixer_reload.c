#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* levels; } ;
typedef  TYPE_1__ sb_devc ;

/* Variables and functions */
 int /*<<< orphan*/  sb_common_mixer_set (TYPE_1__*,int,int,int) ; 

void ess_mixer_reload (sb_devc *devc, int dev)
{
	int left, right, value;

	value = devc->levels[dev];
	left  = value & 0x000000ff;
	right = (value & 0x0000ff00) >> 8;

	sb_common_mixer_set(devc, dev, left, right);
}