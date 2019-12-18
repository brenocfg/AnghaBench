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
struct pcmcia_low_level {int first; int nr; } ;
struct device {struct pcmcia_low_level* platform_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MECR ; 
 int /*<<< orphan*/  MECR_CIT ; 
 int /*<<< orphan*/  MECR_NOS ; 
 scalar_t__ machine_is_viper () ; 

__attribute__((used)) static void pxa2xx_configure_sockets(struct device *dev)
{
	struct pcmcia_low_level *ops = dev->platform_data;

	/*
	 * We have at least one socket, so set MECR:CIT
	 * (Card Is There)
	 */
	MECR |= MECR_CIT;

	/* Set MECR:NOS (Number Of Sockets) */
	if ((ops->first + ops->nr) > 1 || machine_is_viper())
		MECR |= MECR_NOS;
	else
		MECR &= ~MECR_NOS;
}