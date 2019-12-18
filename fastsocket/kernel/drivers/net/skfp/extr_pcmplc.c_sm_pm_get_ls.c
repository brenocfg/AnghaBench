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
struct s_smc {int dummy; } ;

/* Variables and functions */
 int PC_HLS ; 
 int PC_ILS ; 
 int PC_LS_NONE ; 
 int PC_LS_PDR ; 
 int PC_MLS ; 
 int PC_QLS ; 
 int /*<<< orphan*/  PLC (int,int /*<<< orphan*/ ) ; 
 int PL_LINE_ST ; 
#define  PL_L_ALS 133 
#define  PL_L_HLS 132 
#define  PL_L_ILS16 131 
#define  PL_L_ILS4 130 
#define  PL_L_MLS 129 
#define  PL_L_QLS 128 
 int /*<<< orphan*/  PL_STATUS_A ; 
 int inpw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plc_is_installed (struct s_smc*,int) ; 

int sm_pm_get_ls(struct s_smc *smc, int phy)
{
	int	state ;

#ifdef	CONCENTRATOR
	if (!plc_is_installed(smc,phy))
		return(PC_QLS) ;
#endif

	state = inpw(PLC(phy,PL_STATUS_A)) & PL_LINE_ST ;
	switch(state) {
	case PL_L_QLS:
		state = PC_QLS ;
		break ;
	case PL_L_MLS:
		state = PC_MLS ;
		break ;
	case PL_L_HLS:
		state = PC_HLS ;
		break ;
	case PL_L_ILS4:
	case PL_L_ILS16:
		state = PC_ILS ;
		break ;
	case PL_L_ALS:
		state = PC_LS_PDR ;
		break ;
	default :
		state = PC_LS_NONE ;
	}
	return(state) ;
}