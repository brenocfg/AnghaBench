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
 int /*<<< orphan*/  CR99 ; 
 int /*<<< orphan*/  VIACR ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 
 int viafb_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int viafb_dfpl_proc_show(struct seq_file *m, void *v)
{
	u8 dfp_low = 0;
	dfp_low = viafb_read_reg(VIACR, CR99) & 0x0f;
	seq_printf(m, "%x\n", dfp_low);
	return 0;
}