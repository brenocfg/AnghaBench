#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char trace_prop; int /*<<< orphan*/  path_test; } ;
struct TYPE_3__ {int sas; } ;
struct s_smc {TYPE_2__ e; TYPE_1__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  DB_ECM (char*,char,int) ; 
 int ENTITY_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENTITY_MAC ; 
 int /*<<< orphan*/  ENTITY_PHY (int) ; 
 scalar_t__ EVENT_PCM ; 
 scalar_t__ EVENT_PCMA ; 
 scalar_t__ EVENT_PCMB ; 
 char PA ; 
 int PB ; 
 int /*<<< orphan*/  PC_TRACE ; 
 int /*<<< orphan*/  PT_PENDING ; 
 int /*<<< orphan*/  RS_EVENT ; 
 int /*<<< orphan*/  RS_SET (struct s_smc*,int /*<<< orphan*/ ) ; 
#define  SMT_DAS 130 
 int /*<<< orphan*/  SMT_E0108 ; 
 int /*<<< orphan*/  SMT_E0108_MSG ; 
#define  SMT_NAC 129 
 int /*<<< orphan*/  SMT_PANIC (struct s_smc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  SMT_SAS 128 
 int cfm_get_mac_input (struct s_smc*) ; 
 int cfm_get_mac_output (struct s_smc*) ; 
 int pcm_get_s_port (struct s_smc*) ; 
 int /*<<< orphan*/  queue_event (struct s_smc*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void prop_actions(struct s_smc *smc)
{
	int	port_in = 0 ;
	int	port_out = 0 ;

	RS_SET(smc,RS_EVENT) ;
	switch (smc->s.sas) {
	case SMT_SAS :
		port_in = port_out = pcm_get_s_port(smc) ;
		break ;
	case SMT_DAS :
		port_in = cfm_get_mac_input(smc) ;	/* PA or PB */
		port_out = cfm_get_mac_output(smc) ;	/* PA or PB */
		break ;
	case SMT_NAC :
		SMT_PANIC(smc,SMT_E0108, SMT_E0108_MSG) ;
		return ;
	}

	DB_ECM("ECM : prop_actions - trace_prop %d\n", smc->e.trace_prop,0) ;
	DB_ECM("ECM : prop_actions - in %d out %d\n", port_in,port_out) ;

	if (smc->e.trace_prop & ENTITY_BIT(ENTITY_MAC)) {
		/* trace initiatior */
		DB_ECM("ECM : initiate TRACE on PHY %c\n",'A'+port_in-PA,0) ;
		queue_event(smc,EVENT_PCM+port_in,PC_TRACE) ;
	}
	else if ((smc->e.trace_prop & ENTITY_BIT(ENTITY_PHY(PA))) &&
		port_out != PA) {
		/* trace propagate upstream */
		DB_ECM("ECM : propagate TRACE on PHY B\n",0,0) ;
		queue_event(smc,EVENT_PCMB,PC_TRACE) ;
	}
	else if ((smc->e.trace_prop & ENTITY_BIT(ENTITY_PHY(PB))) &&
		port_out != PB) {
		/* trace propagate upstream */
		DB_ECM("ECM : propagate TRACE on PHY A\n",0,0) ;
		queue_event(smc,EVENT_PCMA,PC_TRACE) ;
	}
	else {
		/* signal trace termination */
		DB_ECM("ECM : TRACE terminated\n",0,0) ;
		smc->e.path_test = PT_PENDING ;
	}
	smc->e.trace_prop = 0 ;
}