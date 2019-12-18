#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct soc_pcmcia_socket {int dummy; } ;
struct pcmcia_socket {int dummy; } ;
struct TYPE_4__ {int csc_mask; int flags; int /*<<< orphan*/  io_irq; int /*<<< orphan*/  Vpp; int /*<<< orphan*/  Vcc; } ;
typedef  TYPE_1__ socket_state_t ;

/* Variables and functions */
 int SS_BATDEAD ; 
 int SS_BATWARN ; 
 int SS_DETECT ; 
 int SS_IOCARD ; 
 int SS_OUTPUT_ENA ; 
 int SS_PWR_AUTO ; 
 int SS_READY ; 
 int SS_RESET ; 
 int SS_SPKR_ENA ; 
 int SS_STSCHG ; 
 int /*<<< orphan*/  debug (struct soc_pcmcia_socket*,int,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int soc_common_pcmcia_config_skt (struct soc_pcmcia_socket*,TYPE_1__*) ; 
 struct soc_pcmcia_socket* to_soc_pcmcia_socket (struct pcmcia_socket*) ; 

__attribute__((used)) static int
soc_common_pcmcia_set_socket(struct pcmcia_socket *sock, socket_state_t *state)
{
	struct soc_pcmcia_socket *skt = to_soc_pcmcia_socket(sock);

	debug(skt, 2, "mask: %s%s%s%s%s%sflags: %s%s%s%s%s%sVcc %d Vpp %d irq %d\n",
			(state->csc_mask==0)?"<NONE> ":"",
			(state->csc_mask&SS_DETECT)?"DETECT ":"",
			(state->csc_mask&SS_READY)?"READY ":"",
			(state->csc_mask&SS_BATDEAD)?"BATDEAD ":"",
			(state->csc_mask&SS_BATWARN)?"BATWARN ":"",
			(state->csc_mask&SS_STSCHG)?"STSCHG ":"",
			(state->flags==0)?"<NONE> ":"",
			(state->flags&SS_PWR_AUTO)?"PWR_AUTO ":"",
			(state->flags&SS_IOCARD)?"IOCARD ":"",
			(state->flags&SS_RESET)?"RESET ":"",
			(state->flags&SS_SPKR_ENA)?"SPKR_ENA ":"",
			(state->flags&SS_OUTPUT_ENA)?"OUTPUT_ENA ":"",
			state->Vcc, state->Vpp, state->io_irq);

	return soc_common_pcmcia_config_skt(skt, state);
}