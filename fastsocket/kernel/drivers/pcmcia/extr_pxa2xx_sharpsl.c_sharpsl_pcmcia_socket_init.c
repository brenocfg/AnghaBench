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
struct soc_pcmcia_socket {size_t nr; } ;
struct TYPE_2__ {int /*<<< orphan*/  keep_vs; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NO_KEEP_VS ; 
 TYPE_1__* SCOOP_DEV ; 
 int /*<<< orphan*/  SCOOP_IMR ; 
 int /*<<< orphan*/  SCOOP_MCR ; 
 int /*<<< orphan*/  sharpsl_pcmcia_init_reset (struct soc_pcmcia_socket*) ; 
 int /*<<< orphan*/  write_scoop_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sharpsl_pcmcia_socket_init(struct soc_pcmcia_socket *skt)
{
	sharpsl_pcmcia_init_reset(skt);

	/* Enable interrupt */
	write_scoop_reg(SCOOP_DEV[skt->nr].dev, SCOOP_IMR, 0x00C0);
	write_scoop_reg(SCOOP_DEV[skt->nr].dev, SCOOP_MCR, 0x0101);
	SCOOP_DEV[skt->nr].keep_vs = NO_KEEP_VS;
}