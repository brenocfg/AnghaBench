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
struct svc_export {int ex_nflavors; int /*<<< orphan*/  ex_flags; struct exp_flavor_info* ex_flavors; } ;
struct seq_file {int dummy; } ;
struct exp_flavor_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  secinfo_flags_equal (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_secinfo_flags (struct seq_file*,int) ; 
 int show_secinfo_run (struct seq_file*,struct exp_flavor_info**,struct exp_flavor_info*) ; 

__attribute__((used)) static void show_secinfo(struct seq_file *m, struct svc_export *exp)
{
	struct exp_flavor_info *f;
	struct exp_flavor_info *end = exp->ex_flavors + exp->ex_nflavors;
	int flags;

	if (exp->ex_nflavors == 0)
		return;
	f = exp->ex_flavors;
	flags = show_secinfo_run(m, &f, end);
	if (!secinfo_flags_equal(flags, exp->ex_flags))
		show_secinfo_flags(m, flags);
	while (f != end) {
		flags = show_secinfo_run(m, &f, end);
		show_secinfo_flags(m, flags);
	}
}