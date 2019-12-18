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
 unsigned short DMAOR_AE ; 
 unsigned short DMAOR_NMIF ; 
 unsigned short dmaor_read_reg (int) ; 
 int /*<<< orphan*/  dmaor_write_reg (int,unsigned short) ; 

__attribute__((used)) static void sh_dmae_ctl_stop(int id)
{
	unsigned short dmaor = dmaor_read_reg(id);

	dmaor &= ~(DMAOR_NMIF | DMAOR_AE);
	dmaor_write_reg(id, dmaor);
}