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
typedef  int /*<<< orphan*/  work32 ;
typedef  int u8 ;
typedef  int u32 ;
typedef  char* u16 ;
struct seq_file {scalar_t__ private; } ;
struct i2o_controller {int /*<<< orphan*/  exec; } ;

/* Variables and functions */
 int i2o_parm_field_get (int /*<<< orphan*/ ,int,int,int**,int) ; 
 int /*<<< orphan*/  i2o_report_query_status (struct seq_file*,int,char*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static int i2o_seq_show_hw(struct seq_file *seq, void *v)
{
	struct i2o_controller *c = (struct i2o_controller *)seq->private;
	static u32 work32[5];
	static u8 *work8 = (u8 *) work32;
	static u16 *work16 = (u16 *) work32;
	int token;
	u32 hwcap;

	static char *cpu_table[] = {
		"Intel 80960 series",
		"AMD2900 series",
		"Motorola 68000 series",
		"ARM series",
		"MIPS series",
		"Sparc series",
		"PowerPC series",
		"Intel x86 series"
	};

	token =
	    i2o_parm_field_get(c->exec, 0x0000, -1, &work32, sizeof(work32));

	if (token < 0) {
		i2o_report_query_status(seq, token, "0x0000 IOP Hardware");
		return 0;
	}

	seq_printf(seq, "I2O Vendor ID    : %0#6x\n", work16[0]);
	seq_printf(seq, "Product ID       : %0#6x\n", work16[1]);
	seq_printf(seq, "CPU              : ");
	if (work8[16] > 8)
		seq_printf(seq, "Unknown\n");
	else
		seq_printf(seq, "%s\n", cpu_table[work8[16]]);
	/* Anyone using ProcessorVersion? */

	seq_printf(seq, "RAM              : %dkB\n", work32[1] >> 10);
	seq_printf(seq, "Non-Volatile Mem : %dkB\n", work32[2] >> 10);

	hwcap = work32[3];
	seq_printf(seq, "Capabilities : 0x%08x\n", hwcap);
	seq_printf(seq, "   [%s] Self booting\n",
		   (hwcap & 0x00000001) ? "+" : "-");
	seq_printf(seq, "   [%s] Upgradable IRTOS\n",
		   (hwcap & 0x00000002) ? "+" : "-");
	seq_printf(seq, "   [%s] Supports downloading DDMs\n",
		   (hwcap & 0x00000004) ? "+" : "-");
	seq_printf(seq, "   [%s] Supports installing DDMs\n",
		   (hwcap & 0x00000008) ? "+" : "-");
	seq_printf(seq, "   [%s] Battery-backed RAM\n",
		   (hwcap & 0x00000010) ? "+" : "-");

	return 0;
}