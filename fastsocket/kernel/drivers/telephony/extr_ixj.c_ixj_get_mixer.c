#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* vol; } ;
struct TYPE_5__ {TYPE_1__ mix; } ;
typedef  TYPE_2__ IXJ ;

/* Variables and functions */

__attribute__((used)) static int ixj_get_mixer(long val, IXJ *j)
{
	int reg = (val & 0x1F00) >> 8;
        return j->mix.vol[reg];
}