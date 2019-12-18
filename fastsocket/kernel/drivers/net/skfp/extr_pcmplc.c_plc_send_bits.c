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
struct TYPE_3__ {int d_plc; } ;
struct s_smc {TYPE_1__ debug; } ;
struct s_phy {int np; int* t_val; int bitn; } ;
struct TYPE_4__ {int d_plc; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLC (int,int /*<<< orphan*/ ) ; 
 int PL_PCM_SIGNAL ; 
 int /*<<< orphan*/  PL_STATUS_B ; 
 int /*<<< orphan*/  PL_VECTOR_LEN ; 
 int /*<<< orphan*/  PL_XMIT_VECTOR ; 
 int /*<<< orphan*/  SK_UNUSED (struct s_smc*) ; 
 TYPE_2__ debug ; 
 int inpw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outpw (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int plc_send_bits(struct s_smc *smc, struct s_phy *phy, int len)
{
	int np = phy->np ;		/* PHY index */
	int	n ;
	int	i ;

	SK_UNUSED(smc) ;

	/* create bit vector */
	for (i = len-1,n = 0 ; i >= 0 ; i--) {
		n = (n<<1) | phy->t_val[phy->bitn+i] ;
	}
	if (inpw(PLC(np,PL_STATUS_B)) & PL_PCM_SIGNAL) {
#if	0
		printf("PL_PCM_SIGNAL is set\n") ;
#endif
		return(1) ;
	}
	/* write bit[n] & length = 1 to regs */
	outpw(PLC(np,PL_VECTOR_LEN),len-1) ;	/* len=nr-1 */
	outpw(PLC(np,PL_XMIT_VECTOR),n) ;
#ifdef	DEBUG
#if 1
#ifdef	DEBUG_BRD
	if (smc->debug.d_plc & 0x80)
#else
	if (debug.d_plc & 0x80)
#endif
		printf("SIGNALING bit %d .. %d\n",phy->bitn,phy->bitn+len-1) ;
#endif
#endif
	return(0) ;
}