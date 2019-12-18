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
struct s_smc {TYPE_1__* y; } ;
struct lem_counter {int lem_on; long lem_errors; } ;
struct TYPE_2__ {struct lem_counter lem; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLC (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PL_INTR_MASK ; 
 int /*<<< orphan*/  PL_LE_CTR ; 
 int /*<<< orphan*/  PL_LE_THRESHOLD ; 
 int /*<<< orphan*/  PL_LINK_ERR_CTR ; 
 int /*<<< orphan*/  SETMASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inpw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outpw (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sm_ph_lem_start(struct s_smc *smc, int np, int threshold)
{
	struct lem_counter *lem = &smc->y[np].lem ;

	lem->lem_on = 1 ;
	lem->lem_errors = 0L ;

	/* Do NOT reset mib->fddiPORTLer_Estimate here. It is called too
	 * often.
	 */

	outpw(PLC(np,PL_LE_THRESHOLD),threshold) ;
	(void)inpw(PLC(np,PL_LINK_ERR_CTR)) ;	/* clear error counter */

	/* enable LE INT */
	SETMASK(PLC(np,PL_INTR_MASK),PL_LE_CTR,PL_LE_CTR) ;
}