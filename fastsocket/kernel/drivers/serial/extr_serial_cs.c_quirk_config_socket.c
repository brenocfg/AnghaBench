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
struct serial_info {scalar_t__ multi; } ;
struct TYPE_2__ {int /*<<< orphan*/  ExtStatus; int /*<<< orphan*/  Present; } ;
struct pcmcia_device {TYPE_1__ conf; struct serial_info* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESR_REQ_ATTN_ENA ; 
 int /*<<< orphan*/  PRESENT_EXT_STATUS ; 

__attribute__((used)) static void quirk_config_socket(struct pcmcia_device *link)
{
	struct serial_info *info = link->priv;

	if (info->multi) {
		link->conf.Present |= PRESENT_EXT_STATUS;
		link->conf.ExtStatus = ESR_REQ_ATTN_ENA;
	}
}