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
struct TYPE_3__ {void* pass_llc_promisc; void* pass_DB; void* pass_NSA; void* pass_SMT; } ;
struct TYPE_4__ {TYPE_1__ hwm; } ;
struct s_smc {TYPE_2__ os; } ;

/* Variables and functions */
 void* FALSE ; 
#define  RX_DISABLE_ALLMULTI 142 
#define  RX_DISABLE_LLC_PROMISC 141 
#define  RX_DISABLE_NSA 140 
#define  RX_DISABLE_PASS_ALL 139 
#define  RX_DISABLE_PASS_DB 138 
#define  RX_DISABLE_PASS_NSA 137 
#define  RX_DISABLE_PASS_SMT 136 
#define  RX_DISABLE_PROMISC 135 
#define  RX_ENABLE_ALLMULTI 134 
#define  RX_ENABLE_LLC_PROMISC 133 
#define  RX_ENABLE_NSA 132 
#define  RX_ENABLE_PASS_DB 131 
#define  RX_ENABLE_PASS_NSA 130 
#define  RX_ENABLE_PASS_SMT 129 
#define  RX_ENABLE_PROMISC 128 
 void* TRUE ; 
 int /*<<< orphan*/  mac_set_rx_mode (struct s_smc*,int) ; 

void mac_drv_rx_mode(struct s_smc *smc, int mode)
{
	switch(mode) {
	case RX_ENABLE_PASS_SMT:
		smc->os.hwm.pass_SMT = TRUE ;
		break ;
	case RX_DISABLE_PASS_SMT:
		smc->os.hwm.pass_SMT = FALSE ;
		break ;
	case RX_ENABLE_PASS_NSA:
		smc->os.hwm.pass_NSA = TRUE ;
		break ;
	case RX_DISABLE_PASS_NSA:
		smc->os.hwm.pass_NSA = FALSE ;
		break ;
	case RX_ENABLE_PASS_DB:
		smc->os.hwm.pass_DB = TRUE ;
		break ;
	case RX_DISABLE_PASS_DB:
		smc->os.hwm.pass_DB = FALSE ;
		break ;
	case RX_DISABLE_PASS_ALL:
		smc->os.hwm.pass_SMT = smc->os.hwm.pass_NSA = FALSE ;
		smc->os.hwm.pass_DB = FALSE ;
		smc->os.hwm.pass_llc_promisc = TRUE ;
		mac_set_rx_mode(smc,RX_DISABLE_NSA) ;
		break ;
	case RX_DISABLE_LLC_PROMISC:
		smc->os.hwm.pass_llc_promisc = FALSE ;
		break ;
	case RX_ENABLE_LLC_PROMISC:
		smc->os.hwm.pass_llc_promisc = TRUE ;
		break ;
	case RX_ENABLE_ALLMULTI:
	case RX_DISABLE_ALLMULTI:
	case RX_ENABLE_PROMISC:
	case RX_DISABLE_PROMISC:
	case RX_ENABLE_NSA:
	case RX_DISABLE_NSA:
	default:
		mac_set_rx_mode(smc,mode) ;
		break ;
	}
}