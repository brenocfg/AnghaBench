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
typedef  scalar_t__ u_int ;
struct ahc_softc {int msgout_len; scalar_t__ msgout_index; scalar_t__ msgout_buf; } ;
struct ahc_devinfo {int channel; int target; int lun; } ;

/* Variables and functions */
 scalar_t__ AHC_ASYNC_XFER_PERIOD ; 
 char* ahc_name (struct ahc_softc*) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ spi_populate_ppr_msg (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
ahc_construct_ppr(struct ahc_softc *ahc, struct ahc_devinfo *devinfo,
		  u_int period, u_int offset, u_int bus_width,
		  u_int ppr_options)
{
	if (offset == 0)
		period = AHC_ASYNC_XFER_PERIOD;
	ahc->msgout_index += spi_populate_ppr_msg(
			ahc->msgout_buf + ahc->msgout_index, period, offset,
			bus_width, ppr_options);
	ahc->msgout_len += 8;
	if (bootverbose) {
		printf("(%s:%c:%d:%d): Sending PPR bus_width %x, period %x, "
		       "offset %x, ppr_options %x\n", ahc_name(ahc),
		       devinfo->channel, devinfo->target, devinfo->lun,
		       bus_width, period, offset, ppr_options);
	}
}