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
typedef  enum ipu_channel { ____Placeholder_ipu_channel } ipu_channel ;

/* Variables and functions */
 int /*<<< orphan*/  IPU_CHA_BUF0_RDY ; 
 int /*<<< orphan*/  IPU_CHA_BUF1_RDY ; 
 int /*<<< orphan*/  idmac_write_ipureg (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_data ; 

__attribute__((used)) static void ipu_select_buffer(enum ipu_channel channel, int buffer_n)
{
	/* No locking - this is a write-one-to-set register, cleared by IPU */
	if (buffer_n == 0)
		/* Mark buffer 0 as ready. */
		idmac_write_ipureg(&ipu_data, 1UL << channel, IPU_CHA_BUF0_RDY);
	else
		/* Mark buffer 1 as ready. */
		idmac_write_ipureg(&ipu_data, 1UL << channel, IPU_CHA_BUF1_RDY);
}