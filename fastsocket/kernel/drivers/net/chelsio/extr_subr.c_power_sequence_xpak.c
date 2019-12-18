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
typedef  int u32 ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_ELMER0_GPI_STAT ; 
 int /*<<< orphan*/  A_ELMER0_GPO ; 
 int ELMER0_GP_BIT18 ; 
 int ELMER0_GP_BIT5 ; 
 int /*<<< orphan*/  t1_tpi_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  t1_tpi_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void power_sequence_xpak(adapter_t* adapter)
{
	u32 mod_detect;
	u32 gpo;

	/* Check for XPAK */
	t1_tpi_read(adapter, A_ELMER0_GPI_STAT, &mod_detect);
	if (!(ELMER0_GP_BIT5 & mod_detect)) {
		/* XPAK is present */
		t1_tpi_read(adapter, A_ELMER0_GPO, &gpo);
		gpo |= ELMER0_GP_BIT18;
		t1_tpi_write(adapter, A_ELMER0_GPO, gpo);
	}
}