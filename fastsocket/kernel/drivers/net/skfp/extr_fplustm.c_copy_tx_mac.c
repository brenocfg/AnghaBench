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
typedef  int /*<<< orphan*/  u_long ;
struct s_smc {int dummy; } ;
struct fddi_mac {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_NPP () ; 
 int /*<<< orphan*/  FM_A (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM_CMDREG2 ; 
 int /*<<< orphan*/  FM_ISTTB ; 
 int /*<<< orphan*/  MARW (unsigned int) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outpw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_mdr (struct s_smc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void copy_tx_mac(struct s_smc *smc, u_long td, struct fddi_mac *mac,
			unsigned off, int len)
/* u_long td;		 transmit descriptor */
/* struct fddi_mac *mac; mac frame pointer */
/* unsigned off;	 start address within buffer memory */
/* int len ;		 length of the frame including the FC */
{
	int	i ;
	__le32	*p ;

	CHECK_NPP() ;
	MARW(off) ;		/* set memory address reg for writes */

	p = (__le32 *) mac ;
	for (i = (len + 3)/4 ; i ; i--) {
		if (i == 1) {
			/* last word, set the tag bit */
			outpw(FM_A(FM_CMDREG2),FM_ISTTB) ;
		}
		write_mdr(smc,le32_to_cpu(*p)) ;
		p++ ;
	}

	outpw(FM_A(FM_CMDREG2),FM_ISTTB) ;	/* set the tag bit */
	write_mdr(smc,td) ;	/* write over memory data reg to buffer */
}