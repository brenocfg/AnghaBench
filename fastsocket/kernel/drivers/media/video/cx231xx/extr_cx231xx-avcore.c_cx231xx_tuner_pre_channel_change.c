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
struct cx231xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIF_AGC_IF_REF ; 
 int FLD_DIF_K_AGC_IF ; 
 int FLD_DIF_K_AGC_RF ; 
 int vid_blk_read_word (struct cx231xx*,int /*<<< orphan*/ ,int*) ; 
 int vid_blk_write_word (struct cx231xx*,int /*<<< orphan*/ ,int) ; 

int cx231xx_tuner_pre_channel_change(struct cx231xx *dev)
{
	int status = 0;
	u32 dwval;

	/* Set the RF and IF k_agc values to 3 */
	status = vid_blk_read_word(dev, DIF_AGC_IF_REF, &dwval);
	dwval &= ~(FLD_DIF_K_AGC_RF | FLD_DIF_K_AGC_IF);
	dwval |= 0x33000000;

	status = vid_blk_write_word(dev, DIF_AGC_IF_REF, dwval);

	return status;
}