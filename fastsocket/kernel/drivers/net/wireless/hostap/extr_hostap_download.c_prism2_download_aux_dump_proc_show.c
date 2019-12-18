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
struct seq_file {struct prism2_download_aux_dump* private; } ;
struct prism2_download_aux_dump {int /*<<< orphan*/  page; TYPE_1__* local; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  hfa384x_from_aux (int /*<<< orphan*/ ,unsigned long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_write (struct seq_file*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int prism2_download_aux_dump_proc_show(struct seq_file *m, void *v)
{
	struct prism2_download_aux_dump *ctx = m->private;

	hfa384x_from_aux(ctx->local->dev, (unsigned long)v - 1, 0x80, ctx->page);
	seq_write(m, ctx->page, 0x80);
	return 0;
}