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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int u_int ;
struct ahd_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_ASSERT_MODES (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AHD_MODE_SCSI_MSK ; 
 int /*<<< orphan*/  BRDCTL ; 
 int /*<<< orphan*/  BRDDAT ; 
 int BRDEN ; 
 int BRDRW ; 
 int /*<<< orphan*/  ahd_flush_device_writes (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_inb (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_outb (struct ahd_softc*,int /*<<< orphan*/ ,int) ; 
 int ahd_wait_flexport (struct ahd_softc*) ; 
 int /*<<< orphan*/  panic (char*) ; 

int
ahd_read_flexport(struct ahd_softc *ahd, u_int addr, uint8_t *value)
{
	int	error;

	AHD_ASSERT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);
	if (addr > 7)
		panic("ahd_read_flexport: address out of range");
	ahd_outb(ahd, BRDCTL, BRDRW|BRDEN|(addr << 3));
	error = ahd_wait_flexport(ahd);
	if (error != 0)
		return (error);
	*value = ahd_inb(ahd, BRDDAT);
	ahd_outb(ahd, BRDCTL, 0);
	ahd_flush_device_writes(ahd);
	return (0);
}