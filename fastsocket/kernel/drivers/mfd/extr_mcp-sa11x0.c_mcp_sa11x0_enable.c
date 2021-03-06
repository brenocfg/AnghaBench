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
struct mcp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCCR0_MCE ; 
 int /*<<< orphan*/  Ser4MCCR0 ; 
 int Ser4MCSR ; 

__attribute__((used)) static void mcp_sa11x0_enable(struct mcp *mcp)
{
	Ser4MCSR = -1;
	Ser4MCCR0 |= MCCR0_MCE;
}