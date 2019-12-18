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
struct lance_regs {int rdp; int /*<<< orphan*/  rap; } ;
struct lance_private {int busmaster_regval; struct lance_init_block* lance_init_block; struct lance_regs* ll; } ;
struct lance_init_block {int dummy; } ;

/* Variables and functions */
 int LANCE_ADDR (struct lance_init_block volatile*) ; 
 int /*<<< orphan*/  LE_CSR0 ; 
 int /*<<< orphan*/  LE_CSR1 ; 
 int /*<<< orphan*/  LE_CSR2 ; 
 int /*<<< orphan*/  LE_CSR3 ; 

__attribute__((used)) static void load_csrs (struct lance_private *lp)
{
	volatile struct lance_regs *ll = lp->ll;
	volatile struct lance_init_block *aib = lp->lance_init_block;
	int leptr;

	leptr = LANCE_ADDR (aib);

	ll->rap = LE_CSR1;
	ll->rdp = (leptr & 0xFFFF);
	ll->rap = LE_CSR2;
	ll->rdp = leptr >> 16;
	ll->rap = LE_CSR3;
	ll->rdp = lp->busmaster_regval;

	/* Point back to csr0 */
	ll->rap = LE_CSR0;
}