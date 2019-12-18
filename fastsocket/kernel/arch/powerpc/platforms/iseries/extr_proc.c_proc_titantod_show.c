#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct TYPE_2__ {unsigned long xProcFreq; unsigned long xTimeBaseFreq; } ;

/* Variables and functions */
 int HZ ; 
 unsigned long HvCallXm_loadTod () ; 
 unsigned long get_tb () ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 unsigned long startTb ; 
 unsigned long startTitan ; 
 unsigned long tb_ticks_per_jiffy ; 
 unsigned long tb_ticks_per_usec ; 
 TYPE_1__* xIoHriProcessorVpd ; 

__attribute__((used)) static int proc_titantod_show(struct seq_file *m, void *v)
{
	unsigned long tb0, titan_tod;

	tb0 = get_tb();
	titan_tod = HvCallXm_loadTod();

	seq_printf(m, "Titan\n" );
	seq_printf(m, "  time base =          %016lx\n", tb0);
	seq_printf(m, "  titan tod =          %016lx\n", titan_tod);
	seq_printf(m, "  xProcFreq =          %016x\n",
		   xIoHriProcessorVpd[0].xProcFreq);
	seq_printf(m, "  xTimeBaseFreq =      %016x\n",
		   xIoHriProcessorVpd[0].xTimeBaseFreq);
	seq_printf(m, "  tb_ticks_per_jiffy = %lu\n", tb_ticks_per_jiffy);
	seq_printf(m, "  tb_ticks_per_usec  = %lu\n", tb_ticks_per_usec);

	if (!startTitan) {
		startTitan = titan_tod;
		startTb = tb0;
	} else {
		unsigned long titan_usec = (titan_tod - startTitan) >> 12;
		unsigned long tb_ticks = (tb0 - startTb);
		unsigned long titan_jiffies = titan_usec / (1000000/HZ);
		unsigned long titan_jiff_usec = titan_jiffies * (1000000/HZ);
		unsigned long titan_jiff_rem_usec =
			titan_usec - titan_jiff_usec;
		unsigned long tb_jiffies = tb_ticks / tb_ticks_per_jiffy;
		unsigned long tb_jiff_ticks = tb_jiffies * tb_ticks_per_jiffy;
		unsigned long tb_jiff_rem_ticks = tb_ticks - tb_jiff_ticks;
		unsigned long tb_jiff_rem_usec =
			tb_jiff_rem_ticks / tb_ticks_per_usec;
		unsigned long new_tb_ticks_per_jiffy =
			(tb_ticks * (1000000/HZ))/titan_usec;

		seq_printf(m, "  titan elapsed = %lu uSec\n", titan_usec);
		seq_printf(m, "  tb elapsed    = %lu ticks\n", tb_ticks);
		seq_printf(m, "  titan jiffies = %lu.%04lu \n", titan_jiffies,
			   titan_jiff_rem_usec);
		seq_printf(m, "  tb jiffies    = %lu.%04lu\n", tb_jiffies,
			   tb_jiff_rem_usec);
		seq_printf(m, "  new tb_ticks_per_jiffy = %lu\n",
			   new_tb_ticks_per_jiffy);
	}

	return 0;
}