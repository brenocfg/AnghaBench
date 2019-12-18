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
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  counter; int /*<<< orphan*/  label; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ ) ; 
 TYPE_1__* sctp_dbg_objcnt ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,char*,...) ; 

__attribute__((used)) static int sctp_objcnt_seq_show(struct seq_file *seq, void *v)
{
	int i, len;

	i = (int)*(loff_t *)v;
	seq_printf(seq, "%s: %d%n", sctp_dbg_objcnt[i].label,
				atomic_read(sctp_dbg_objcnt[i].counter), &len);
	seq_printf(seq, "%*s\n", 127 - len, "");
	return 0;
}