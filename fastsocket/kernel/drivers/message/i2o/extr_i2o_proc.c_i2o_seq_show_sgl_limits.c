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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct seq_file {scalar_t__ private; } ;
struct i2o_device {int dummy; } ;

/* Variables and functions */
 int i2o_parm_field_get (struct i2o_device*,int,int,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  i2o_report_query_status (struct seq_file*,int,char*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static int i2o_seq_show_sgl_limits(struct seq_file *seq, void *v)
{
	struct i2o_device *d = (struct i2o_device *)seq->private;
	static u32 work32[12];
	static u16 *work16 = (u16 *) work32;
	static u8 *work8 = (u8 *) work32;
	int token;

	token = i2o_parm_field_get(d, 0xF103, -1, &work32, sizeof(work32));

	if (token < 0) {
		i2o_report_query_status(seq, token,
					"0xF103 SGL Operating Limits");
		return 0;
	}

	seq_printf(seq, "SGL chain size        : %d\n", work32[0]);
	seq_printf(seq, "Max SGL chain size    : %d\n", work32[1]);
	seq_printf(seq, "SGL chain size target : %d\n", work32[2]);
	seq_printf(seq, "SGL frag count        : %d\n", work16[6]);
	seq_printf(seq, "Max SGL frag count    : %d\n", work16[7]);
	seq_printf(seq, "SGL frag count target : %d\n", work16[8]);

/* FIXME
	if (d->i2oversion == 0x02)
	{
*/
	seq_printf(seq, "SGL data alignment    : %d\n", work16[8]);
	seq_printf(seq, "SGL addr limit        : %d\n", work8[20]);
	seq_printf(seq, "SGL addr sizes supported : ");
	if (work8[21] & 0x01)
		seq_printf(seq, "32 bit ");
	if (work8[21] & 0x02)
		seq_printf(seq, "64 bit ");
	if (work8[21] & 0x04)
		seq_printf(seq, "96 bit ");
	if (work8[21] & 0x08)
		seq_printf(seq, "128 bit ");
	seq_printf(seq, "\n");
/*
	}
*/

	return 0;
}