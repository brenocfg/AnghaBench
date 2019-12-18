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
struct smt_para {int dummy; } ;
struct smt_p_setcount {scalar_t__ count; scalar_t__ timestamp; } ;
struct smt_header {int dummy; } ;
struct TYPE_3__ {scalar_t__ count; scalar_t__ timestamp; } ;
struct TYPE_4__ {TYPE_1__ fddiSMTSetCount; } ;
struct s_smc {TYPE_2__ mib; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMT_P1035 ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 scalar_t__ sm_to_para (struct s_smc*,struct smt_header*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smt_check_set_count(struct s_smc *smc, struct smt_header *sm)
{
	struct smt_para	*pa ;
	struct smt_p_setcount	*sc ;

	pa = (struct smt_para *) sm_to_para(smc,sm,SMT_P1035) ;
	if (pa) {
		sc = (struct smt_p_setcount *) pa ;
		if ((smc->mib.fddiSMTSetCount.count != sc->count) ||
			memcmp((char *) smc->mib.fddiSMTSetCount.timestamp,
			(char *)sc->timestamp,8))
			return(1) ;
	}
	return(0) ;
}