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
struct scsi_cmnd {int* cmnd; } ;

/* Variables and functions */
 int /*<<< orphan*/  simscsi_sg_readwrite (struct scsi_cmnd*,int,unsigned long) ; 

__attribute__((used)) static void
simscsi_readwrite6 (struct scsi_cmnd *sc, int mode)
{
	unsigned long offset;

	offset = (((sc->cmnd[1] & 0x1f) << 16) | (sc->cmnd[2] << 8) | sc->cmnd[3])*512;
	simscsi_sg_readwrite(sc, mode, offset);
}