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
struct smt_p_neighbor {int /*<<< orphan*/  nb_dna; int /*<<< orphan*/  nb_una; int /*<<< orphan*/  nb_mac_index; int /*<<< orphan*/  nb_mib_index; } ;
struct TYPE_3__ {TYPE_2__* m; } ;
struct s_smc {TYPE_1__ mib; } ;
struct TYPE_4__ {int /*<<< orphan*/  fddiMACDownstreamNbr; int /*<<< orphan*/  fddiMACUpstreamNbr; } ;

/* Variables and functions */
 int /*<<< orphan*/  INDEX_MAC ; 
 size_t MAC0 ; 
 int /*<<< orphan*/  SMTSETPARA (struct smt_p_neighbor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMT_P_NEIGHBORS ; 
 int /*<<< orphan*/  mac_index (struct s_smc*,int) ; 

__attribute__((used)) static void smt_fill_neighbor(struct s_smc *smc, struct smt_p_neighbor *neighbor)
{
	SMTSETPARA(neighbor,SMT_P_NEIGHBORS) ;

	neighbor->nb_mib_index = INDEX_MAC ;
	neighbor->nb_mac_index = mac_index(smc,1) ;
	neighbor->nb_una = smc->mib.m[MAC0].fddiMACUpstreamNbr ;
	neighbor->nb_dna = smc->mib.m[MAC0].fddiMACDownstreamNbr ;
}