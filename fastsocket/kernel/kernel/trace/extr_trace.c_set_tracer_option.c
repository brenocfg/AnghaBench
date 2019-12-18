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
struct tracer_opt {int /*<<< orphan*/  bit; scalar_t__ name; } ;
struct tracer_flags {int /*<<< orphan*/  val; struct tracer_opt* opts; } ;
struct tracer {int (* set_flag ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;struct tracer_flags* flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int strlen (scalar_t__) ; 
 scalar_t__ strncmp (char*,scalar_t__,int) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int set_tracer_option(struct tracer *trace, char *cmp, int neg)
{
	struct tracer_flags *tracer_flags = trace->flags;
	struct tracer_opt *opts = NULL;
	int ret = 0, i = 0;
	int len;

	for (i = 0; tracer_flags->opts[i].name; i++) {
		opts = &tracer_flags->opts[i];
		len = strlen(opts->name);

		if (strncmp(cmp, opts->name, len) == 0) {
			ret = trace->set_flag(tracer_flags->val,
				opts->bit, !neg);
			break;
		}
	}
	/* Not found */
	if (!tracer_flags->opts[i].name)
		return -EINVAL;

	/* Refused to handle */
	if (ret)
		return ret;

	if (neg)
		tracer_flags->val &= ~opts->bit;
	else
		tracer_flags->val |= opts->bit;

	return 0;
}