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
typedef  int u8 ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 int BIT1 ; 
 int BIT2 ; 
 int BIT4 ; 
 int BIT5 ; 
 int /*<<< orphan*/  CR96 ; 
 int /*<<< orphan*/  SR1B ; 
 int /*<<< orphan*/  SR1E ; 
 int /*<<< orphan*/  SR2A ; 
 int /*<<< orphan*/  VIACR ; 
 int /*<<< orphan*/  VIASR ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,int,int) ; 
 int viafb_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int viafb_dvp0_proc_show(struct seq_file *m, void *v)
{
	u8 dvp0_data_dri = 0, dvp0_clk_dri = 0, dvp0 = 0;
	dvp0_data_dri =
	    (viafb_read_reg(VIASR, SR2A) & BIT5) >> 4 |
	    (viafb_read_reg(VIASR, SR1B) & BIT1) >> 1;
	dvp0_clk_dri =
	    (viafb_read_reg(VIASR, SR2A) & BIT4) >> 3 |
	    (viafb_read_reg(VIASR, SR1E) & BIT2) >> 2;
	dvp0 = viafb_read_reg(VIACR, CR96) & 0x0f;
	seq_printf(m, "%x %x %x\n", dvp0, dvp0_data_dri, dvp0_clk_dri);
	return 0;
}