#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ahd_softc {int seltime; TYPE_1__* platform_data; } ;
struct ahd_platform_data {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_LINUX_NOIRQ ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  ahd_lockinit (struct ahd_softc*) ; 
 int aic79xx_seltime ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int
ahd_platform_alloc(struct ahd_softc *ahd, void *platform_arg)
{
	ahd->platform_data =
	    malloc(sizeof(struct ahd_platform_data), M_DEVBUF, M_NOWAIT);
	if (ahd->platform_data == NULL)
		return (ENOMEM);
	memset(ahd->platform_data, 0, sizeof(struct ahd_platform_data));
	ahd->platform_data->irq = AHD_LINUX_NOIRQ;
	ahd_lockinit(ahd);
	ahd->seltime = (aic79xx_seltime & 0x3) << 4;
	return (0);
}