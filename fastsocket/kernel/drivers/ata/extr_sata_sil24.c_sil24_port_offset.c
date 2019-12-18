#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ata_port {unsigned long port_no; } ;

/* Variables and functions */
 unsigned long PORT_REGS_SIZE ; 

__attribute__((used)) static unsigned long sil24_port_offset(struct ata_port *ap)
{
	return ap->port_no * PORT_REGS_SIZE;
}