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
struct ssp_state {int cr0; int /*<<< orphan*/  cr1; } ;

/* Variables and functions */
 int SSCR0_SSE ; 
 int /*<<< orphan*/  SSSR_ROR ; 
 int Ser4SSCR0 ; 
 int /*<<< orphan*/  Ser4SSCR1 ; 
 int /*<<< orphan*/  Ser4SSSR ; 

void ssp_restore_state(struct ssp_state *ssp)
{
	Ser4SSSR = SSSR_ROR;

	Ser4SSCR0 = ssp->cr0 & ~SSCR0_SSE;
	Ser4SSCR1 = ssp->cr1;
	Ser4SSCR0 = ssp->cr0;
}