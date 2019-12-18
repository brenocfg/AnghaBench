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

/* Variables and functions */
 int /*<<< orphan*/  CSC_CR ; 
 int /*<<< orphan*/  PCC_AWER_B ; 
 int getcsc (int /*<<< orphan*/ ) ; 
 int getpcc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setcsc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setpcc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dnpc_unmap_flash(void)
{
	/* - enable PC Card indexed register space */
	setcsc(CSC_CR, getcsc(CSC_CR) | 0x2);

	/* disable memory window 1 */
	setpcc(PCC_AWER_B, getpcc(PCC_AWER_B) & ~0x02);

	/* now disable PC Card indexed register space again */
	setcsc(CSC_CR, getcsc(CSC_CR) & ~0x2);
}