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
struct soc_pcmcia_timing {int /*<<< orphan*/  io; int /*<<< orphan*/  attr; int /*<<< orphan*/  mem; } ;
struct soc_pcmcia_socket {int nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  pxa2xx_pcmcia_set_mcatt (int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pxa2xx_pcmcia_set_mcio (int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pxa2xx_pcmcia_set_mcmem (int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  soc_common_pcmcia_get_timing (struct soc_pcmcia_socket*,struct soc_pcmcia_timing*) ; 

__attribute__((used)) static int pxa2xx_pcmcia_set_mcxx(struct soc_pcmcia_socket *skt, unsigned int clk)
{
	struct soc_pcmcia_timing timing;
	int sock = skt->nr;

	soc_common_pcmcia_get_timing(skt, &timing);

	pxa2xx_pcmcia_set_mcmem(sock, timing.mem, clk);
	pxa2xx_pcmcia_set_mcatt(sock, timing.attr, clk);
	pxa2xx_pcmcia_set_mcio(sock, timing.io, clk);

	return 0;
}