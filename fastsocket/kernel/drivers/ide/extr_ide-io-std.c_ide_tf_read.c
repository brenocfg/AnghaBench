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
typedef  int u8 ;
struct ide_taskfile {int error; int nsect; int lbal; int lbam; int lbah; int device; } ;
struct ide_io_ports {unsigned long feature_addr; unsigned long nsect_addr; unsigned long lbal_addr; unsigned long lbam_addr; unsigned long lbah_addr; unsigned long device_addr; } ;
struct TYPE_4__ {int host_flags; struct ide_io_ports io_ports; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_5__ {TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int IDE_HFLAG_MMIO ; 
 int IDE_VALID_DEVICE ; 
 int IDE_VALID_ERROR ; 
 int IDE_VALID_LBAH ; 
 int IDE_VALID_LBAL ; 
 int IDE_VALID_LBAM ; 
 int IDE_VALID_NSECT ; 
 int ide_inb (unsigned long) ; 
 int ide_mm_inb (unsigned long) ; 

void ide_tf_read(ide_drive_t *drive, struct ide_taskfile *tf, u8 valid)
{
	ide_hwif_t *hwif = drive->hwif;
	struct ide_io_ports *io_ports = &hwif->io_ports;
	u8 (*tf_inb)(unsigned long port);
	u8 mmio = (hwif->host_flags & IDE_HFLAG_MMIO) ? 1 : 0;

	if (mmio)
		tf_inb  = ide_mm_inb;
	else
		tf_inb  = ide_inb;

	if (valid & IDE_VALID_ERROR)
		tf->error  = tf_inb(io_ports->feature_addr);
	if (valid & IDE_VALID_NSECT)
		tf->nsect  = tf_inb(io_ports->nsect_addr);
	if (valid & IDE_VALID_LBAL)
		tf->lbal   = tf_inb(io_ports->lbal_addr);
	if (valid & IDE_VALID_LBAM)
		tf->lbam   = tf_inb(io_ports->lbam_addr);
	if (valid & IDE_VALID_LBAH)
		tf->lbah   = tf_inb(io_ports->lbah_addr);
	if (valid & IDE_VALID_DEVICE)
		tf->device = tf_inb(io_ports->device_addr);
}