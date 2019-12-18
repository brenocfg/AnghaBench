#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ide_cmd {int dummy; } ;
struct TYPE_7__ {TYPE_2__* hwif; } ;
typedef  TYPE_3__ ide_drive_t ;
struct TYPE_5__ {int /*<<< orphan*/  data_addr; } ;
struct TYPE_6__ {TYPE_1__ io_ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  mm_insw (int /*<<< orphan*/ ,void*,unsigned int) ; 

__attribute__((used)) static void h8300_input_data(ide_drive_t *drive, struct ide_cmd *cmd,
			     void *buf, unsigned int len)
{
	mm_insw(drive->hwif->io_ports.data_addr, buf, (len + 1) / 2);
}