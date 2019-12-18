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

/* Variables and functions */
 int /*<<< orphan*/  SOFT_RST ; 
 int fsi_master_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsi_master_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void fsi_soft_all_reset(void)
{
	u32 status = fsi_master_read(SOFT_RST);

	/* port AB reset */
	status &= 0x000000ff;
	fsi_master_write(SOFT_RST, status);
	mdelay(10);

	/* soft reset */
	status &= 0x000000f0;
	fsi_master_write(SOFT_RST, status);
	status |= 0x00000001;
	fsi_master_write(SOFT_RST, status);
	mdelay(10);
}