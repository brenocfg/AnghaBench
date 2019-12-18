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
struct seq_file {int dummy; } ;
struct direct_tcp_stat {int /*<<< orphan*/  input_route_slow; int /*<<< orphan*/  input_route_fast; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_id ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int direct_tcp_seq_show(struct seq_file *seq, void *v)
{
	struct direct_tcp_stat *s = v;

	seq_printf(seq, "%u\t%-15lu%-15lu\n",
		cpu_id, s->input_route_fast, s->input_route_slow);

	return 0;
}