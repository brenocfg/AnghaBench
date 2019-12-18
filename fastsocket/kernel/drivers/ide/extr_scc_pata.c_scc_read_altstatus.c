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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {scalar_t__ ctl_addr; } ;
struct TYPE_5__ {TYPE_1__ io_ports; } ;
typedef  TYPE_2__ ide_hwif_t ;

/* Variables and functions */
 int /*<<< orphan*/  in_be32 (void*) ; 

__attribute__((used)) static u8 scc_read_altstatus(ide_hwif_t *hwif)
{
	return (u8)in_be32((void *)hwif->io_ports.ctl_addr);
}