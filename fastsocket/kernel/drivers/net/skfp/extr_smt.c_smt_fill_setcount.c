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
struct smt_p_setcount {scalar_t__ timestamp; int /*<<< orphan*/  count; } ;
struct TYPE_3__ {scalar_t__ timestamp; int /*<<< orphan*/  count; } ;
struct TYPE_4__ {TYPE_1__ fddiSMTSetCount; } ;
struct s_smc {TYPE_2__ mib; } ;

/* Variables and functions */
 int /*<<< orphan*/  SK_UNUSED (struct s_smc*) ; 
 int /*<<< orphan*/  SMTSETPARA (struct smt_p_setcount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMT_P_SETCOUNT ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static void smt_fill_setcount(struct s_smc *smc, struct smt_p_setcount *setcount)
{
	SK_UNUSED(smc) ;
	SMTSETPARA(setcount,SMT_P_SETCOUNT) ;
	setcount->count = smc->mib.fddiSMTSetCount.count ;
	memcpy((char *)setcount->timestamp,
		(char *)smc->mib.fddiSMTSetCount.timestamp,8) ;
}