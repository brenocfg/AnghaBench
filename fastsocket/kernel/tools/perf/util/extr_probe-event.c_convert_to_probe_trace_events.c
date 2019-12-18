#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct symbol {scalar_t__ end; scalar_t__ start; } ;
struct TYPE_8__ {scalar_t__ offset; int /*<<< orphan*/ * symbol; int /*<<< orphan*/  retprobe; int /*<<< orphan*/ * module; } ;
struct probe_trace_event {int nargs; TYPE_4__ point; TYPE_3__* args; scalar_t__ uprobes; } ;
struct probe_trace_arg {int dummy; } ;
struct TYPE_5__ {char const* function; scalar_t__ offset; int /*<<< orphan*/  retprobe; } ;
struct perf_probe_event {int nargs; scalar_t__ uprobes; TYPE_2__* args; TYPE_1__ point; } ;
struct TYPE_7__ {int /*<<< orphan*/ * type; int /*<<< orphan*/ * value; int /*<<< orphan*/ * name; } ;
struct TYPE_6__ {char const* name; char const* var; char const* type; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 struct symbol* __find_kernel_function_by_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_probe_trace_event (struct probe_trace_event*) ; 
 int /*<<< orphan*/  free (struct probe_trace_event*) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ *) ; 
 void* strdup (char const*) ; 
 int try_to_find_probe_trace_events (struct perf_probe_event*,struct probe_trace_event**,int,char const*) ; 
 void* zalloc (int) ; 

__attribute__((used)) static int convert_to_probe_trace_events(struct perf_probe_event *pev,
					  struct probe_trace_event **tevs,
					  int max_tevs, const char *target)
{
	struct symbol *sym;
	int ret = 0, i;
	struct probe_trace_event *tev;

	/* Convert perf_probe_event with debuginfo */
	ret = try_to_find_probe_trace_events(pev, tevs, max_tevs, target);
	if (ret != 0)
		return ret;	/* Found in debuginfo or got an error */

	/* Allocate trace event buffer */
	tev = *tevs = zalloc(sizeof(struct probe_trace_event));
	if (tev == NULL)
		return -ENOMEM;

	/* Copy parameters */
	tev->point.symbol = strdup(pev->point.function);
	if (tev->point.symbol == NULL) {
		ret = -ENOMEM;
		goto error;
	}

	if (target) {
		tev->point.module = strdup(target);
		if (tev->point.module == NULL) {
			ret = -ENOMEM;
			goto error;
		}
	}

	tev->point.offset = pev->point.offset;
	tev->point.retprobe = pev->point.retprobe;
	tev->nargs = pev->nargs;
	tev->uprobes = pev->uprobes;

	if (tev->nargs) {
		tev->args = zalloc(sizeof(struct probe_trace_arg)
				   * tev->nargs);
		if (tev->args == NULL) {
			ret = -ENOMEM;
			goto error;
		}
		for (i = 0; i < tev->nargs; i++) {
			if (pev->args[i].name) {
				tev->args[i].name = strdup(pev->args[i].name);
				if (tev->args[i].name == NULL) {
					ret = -ENOMEM;
					goto error;
				}
			}
			tev->args[i].value = strdup(pev->args[i].var);
			if (tev->args[i].value == NULL) {
				ret = -ENOMEM;
				goto error;
			}
			if (pev->args[i].type) {
				tev->args[i].type = strdup(pev->args[i].type);
				if (tev->args[i].type == NULL) {
					ret = -ENOMEM;
					goto error;
				}
			}
		}
	}

	if (pev->uprobes)
		return 1;

	/* Currently just checking function name from symbol map */
	sym = __find_kernel_function_by_name(tev->point.symbol, NULL);
	if (!sym) {
		pr_warning("Kernel symbol \'%s\' not found.\n",
			   tev->point.symbol);
		ret = -ENOENT;
		goto error;
	} else if (tev->point.offset > sym->end - sym->start) {
		pr_warning("Offset specified is greater than size of %s\n",
			   tev->point.symbol);
		ret = -ENOENT;
		goto error;

	}

	return 1;
error:
	clear_probe_trace_event(tev);
	free(tev);
	*tevs = NULL;
	return ret;
}