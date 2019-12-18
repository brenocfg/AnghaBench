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
struct TYPE_2__ {int tnctrl; } ;
struct tea5764_device {TYPE_1__ regs; } ;

/* Variables and functions */
 int TEA5764_TNCTRL_MU ; 

__attribute__((used)) static int tea5764_is_muted(struct tea5764_device *radio)
{
	return radio->regs.tnctrl & TEA5764_TNCTRL_MU;
}