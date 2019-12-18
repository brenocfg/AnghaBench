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
struct dc390_acb {struct dc390_srb* pFreeSRB; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,struct dc390_srb*) ; 

__attribute__((used)) static __inline__ void dc390_Free_insert (struct dc390_acb* pACB, struct dc390_srb* pSRB)
{
    DEBUG0(printk ("DC390: Free SRB %p\n", pSRB));
    pSRB->pNextSRB = pACB->pFreeSRB;
    pACB->pFreeSRB = pSRB;
}