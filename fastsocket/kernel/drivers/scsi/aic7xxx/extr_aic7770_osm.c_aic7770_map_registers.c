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
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_2__ {int /*<<< orphan*/  ioport; } ;
struct ahc_softc {TYPE_1__ bsh; int /*<<< orphan*/  tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHC_EISA_IOSIZE ; 
 int /*<<< orphan*/  BUS_SPACE_PIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  request_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

int
aic7770_map_registers(struct ahc_softc *ahc, u_int port)
{
	/*
	 * Lock out other contenders for our i/o space.
	 */
	if (!request_region(port, AHC_EISA_IOSIZE, "aic7xxx"))
		return (ENOMEM);
	ahc->tag = BUS_SPACE_PIO;
	ahc->bsh.ioport = port;
	return (0);
}