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
struct tracer_opt {scalar_t__ name; } ;
struct tracer_flags {struct tracer_opt* opts; } ;
struct tracer {struct tracer_flags* flags; } ;
struct trace_option_dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  create_trace_option_file (struct trace_option_dentry*,struct tracer_flags*,struct tracer_opt*) ; 
 struct trace_option_dentry* kcalloc (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct trace_option_dentry *
create_trace_option_files(struct tracer *tracer)
{
	struct trace_option_dentry *topts;
	struct tracer_flags *flags;
	struct tracer_opt *opts;
	int cnt;

	if (!tracer)
		return NULL;

	flags = tracer->flags;

	if (!flags || !flags->opts)
		return NULL;

	opts = flags->opts;

	for (cnt = 0; opts[cnt].name; cnt++)
		;

	topts = kcalloc(cnt + 1, sizeof(*topts), GFP_KERNEL);
	if (!topts)
		return NULL;

	for (cnt = 0; opts[cnt].name; cnt++)
		create_trace_option_file(&topts[cnt], flags,
					 &opts[cnt]);

	return topts;
}