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
struct seq_file {struct cgroup_seqfile_state* private; } ;
struct cgroup_seqfile_state {int /*<<< orphan*/  cgroup; struct cftype* cft; } ;
struct cgroup_map_cb {struct seq_file* state; int /*<<< orphan*/  fill; } ;
struct cftype {int (* read_map ) (int /*<<< orphan*/ ,struct cftype*,struct cgroup_map_cb*) ;int (* read_seq_string ) (int /*<<< orphan*/ ,struct cftype*,struct seq_file*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cgroup_map_add ; 
 int stub1 (int /*<<< orphan*/ ,struct cftype*,struct cgroup_map_cb*) ; 
 int stub2 (int /*<<< orphan*/ ,struct cftype*,struct seq_file*) ; 

__attribute__((used)) static int cgroup_seqfile_show(struct seq_file *m, void *arg)
{
	struct cgroup_seqfile_state *state = m->private;
	struct cftype *cft = state->cft;
	if (cft->read_map) {
		struct cgroup_map_cb cb = {
			.fill = cgroup_map_add,
			.state = m,
		};
		return cft->read_map(state->cgroup, cft, &cb);
	}
	return cft->read_seq_string(state->cgroup, cft, m);
}