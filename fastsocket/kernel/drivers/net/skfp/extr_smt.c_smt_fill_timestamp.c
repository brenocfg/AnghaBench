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
struct smt_p_timestamp {int /*<<< orphan*/  ts_time; } ;
struct s_smc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMTSETPARA (struct smt_p_timestamp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMT_P_TIMESTAMP ; 
 int /*<<< orphan*/  smt_set_timestamp (struct s_smc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smt_fill_timestamp(struct s_smc *smc, struct smt_p_timestamp *ts)
{

	SMTSETPARA(ts,SMT_P_TIMESTAMP) ;
	smt_set_timestamp(smc,ts->ts_time) ;
}