#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  nmissed; } ;
struct TYPE_6__ {TYPE_2__ kp; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct trace_probe {TYPE_3__ rp; int /*<<< orphan*/  nhit; TYPE_1__ call; } ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int probes_profile_seq_show(struct seq_file *m, void *v)
{
	struct trace_probe *tp = v;

	seq_printf(m, "  %-44s %15lu %15lu\n", tp->call.name, tp->nhit,
		   tp->rp.kp.nmissed);

	return 0;
}