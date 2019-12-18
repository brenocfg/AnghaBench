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
struct hwicap_drvdata {scalar_t__ base_address; } ;

/* Variables and functions */
 int XHI_CR_FIFO_CLR_MASK ; 
 scalar_t__ XHI_CR_OFFSET ; 
 int in_be32 (scalar_t__) ; 
 int /*<<< orphan*/  out_be32 (scalar_t__,int) ; 

void fifo_icap_flush_fifo(struct hwicap_drvdata *drvdata)
{
	u32 reg_data;
	/*
	 * Flush the FIFO by setting/clearing the FIFO Clear bit in the
	 * Control Register.
	 */
	reg_data = in_be32(drvdata->base_address + XHI_CR_OFFSET);

	out_be32(drvdata->base_address + XHI_CR_OFFSET,
				reg_data | XHI_CR_FIFO_CLR_MASK);

	out_be32(drvdata->base_address + XHI_CR_OFFSET,
				reg_data & (~XHI_CR_FIFO_CLR_MASK));
}