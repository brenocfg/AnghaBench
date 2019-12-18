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
struct dc390_srb {struct dc390_srb* pNextSRB; } ;
struct dc390_dcb {struct dc390_srb* pGoingLast; struct dc390_srb* pGoingSRB; int /*<<< orphan*/  GoingSRBCnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,struct dc390_srb*) ; 

__attribute__((used)) static __inline__ void dc390_Going_append (struct dc390_dcb* pDCB, struct dc390_srb* pSRB)
{
    pDCB->GoingSRBCnt++;
    DEBUG0(printk("DC390: Append SRB %p to Going\n", pSRB));
    /* Append to the list of Going commands */
    if( pDCB->pGoingSRB )
	pDCB->pGoingLast->pNextSRB = pSRB;
    else
	pDCB->pGoingSRB = pSRB;

    pDCB->pGoingLast = pSRB;
    /* No next one in sent list */
    pSRB->pNextSRB = NULL;
}