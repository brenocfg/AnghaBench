#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_char ;
struct TYPE_7__ {void** a; } ;
struct TYPE_6__ {void** a; } ;
struct TYPE_8__ {TYPE_3__ fddi_phys_addr; TYPE_2__ fddi_canon_addr; TYPE_3__ fddi_home_addr; } ;
struct s_smc {TYPE_4__ hw; TYPE_1__* y; } ;
struct TYPE_5__ {char* pmd_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR (scalar_t__) ; 
 scalar_t__ B2_CONN_TYP ; 
 scalar_t__ B2_MAC_0 ; 
 scalar_t__ B2_PMD_TYP ; 
 size_t PA ; 
 size_t PB ; 
 size_t PMD_SK_CONN ; 
 size_t PMD_SK_PMD ; 
 void* bitrev8 (void*) ; 
 void* inp (int /*<<< orphan*/ ) ; 

void read_address(struct s_smc *smc, u_char *mac_addr)
{
	char ConnectorType ;
	char PmdType ;
	int	i ;

#ifdef	PCI
	for (i = 0; i < 6; i++) {	/* read mac address from board */
		smc->hw.fddi_phys_addr.a[i] =
			bitrev8(inp(ADDR(B2_MAC_0+i)));
	}
#endif

	ConnectorType = inp(ADDR(B2_CONN_TYP)) ;
	PmdType = inp(ADDR(B2_PMD_TYP)) ;

	smc->y[PA].pmd_type[PMD_SK_CONN] =
	smc->y[PB].pmd_type[PMD_SK_CONN] = ConnectorType ;
	smc->y[PA].pmd_type[PMD_SK_PMD ] =
	smc->y[PB].pmd_type[PMD_SK_PMD ] = PmdType ;

	if (mac_addr) {
		for (i = 0; i < 6 ;i++) {
			smc->hw.fddi_canon_addr.a[i] = mac_addr[i] ;
			smc->hw.fddi_home_addr.a[i] = bitrev8(mac_addr[i]);
		}
		return ;
	}
	smc->hw.fddi_home_addr = smc->hw.fddi_phys_addr ;

	for (i = 0; i < 6 ;i++) {
		smc->hw.fddi_canon_addr.a[i] =
			bitrev8(smc->hw.fddi_phys_addr.a[i]);
	}
}