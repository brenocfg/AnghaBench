#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct smp_p_user {scalar_t__ us_data; } ;
struct TYPE_2__ {scalar_t__ fddiSMTUserData; } ;
struct s_smc {TYPE_1__ mib; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMTSETPARA (struct smp_p_user*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMT_P_USER ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static void smt_fill_user(struct s_smc *smc, struct smp_p_user *user)
{
	SMTSETPARA(user,SMT_P_USER) ;
	memcpy((char *) user->us_data,
		(char *) smc->mib.fddiSMTUserData,
		sizeof(user->us_data)) ;
}