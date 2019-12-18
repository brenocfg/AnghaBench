#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* ev_name; char ev_type; char* ev_predicate; int /*<<< orphan*/ * ev_acquire; } ;
typedef  TYPE_1__ ls_event_info_t ;
typedef  int /*<<< orphan*/  hrtime_t ;

/* Variables and functions */
 scalar_t__ LS_HIST ; 
 scalar_t__ LS_STACK (int) ; 
 int /*<<< orphan*/  dprog_add (char*,...) ; 
 TYPE_1__* g_event_info ; 
 char* g_ipredicate ; 
 int /*<<< orphan*/ * g_min_duration ; 
 char* g_predicate ; 
 scalar_t__ g_recsize ; 
 scalar_t__ g_tracing ; 
 int /*<<< orphan*/  predicate_add (char**,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  predicate_destroy (char**) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static void
dprog_addevent(int event)
{
	ls_event_info_t *info = &g_event_info[event];
	char *pred = NULL;
	char stack[20];
	const char *arg0, *caller;
	char *arg1 = "arg1";
	char buf[80];
	hrtime_t dur;
	int depth;

	if (info->ev_name[0] == '\0')
		return;

	if (info->ev_type == 'I') {
		/*
		 * For interrupt events, arg0 (normally the lock pointer) is
		 * the CPU address plus the current pil, and arg1 (normally
		 * the number of nanoseconds) is the number of nanoseconds
		 * late -- and it's stored in arg2.
		 */
#ifdef illumos
		arg0 = "(uintptr_t)curthread->t_cpu + \n"
		    "\t    curthread->t_cpu->cpu_profile_pil";
#else
		arg0 = "(uintptr_t)(curthread->td_oncpu << 16) + \n"
		    "\t    0x01000000 + curthread->td_pri_class";
#endif
		caller = "(uintptr_t)arg0";
		arg1 = "arg2";
	} else {
#ifdef illumos
		arg0 = "(uintptr_t)arg0";
#else
		arg0 = "stringof(args[0]->lock_object.lo_name)";
#endif
		caller = "caller";
	}

	if (g_recsize > LS_HIST) {
		for (depth = 0; g_recsize > LS_STACK(depth); depth++)
			continue;

		if (g_tracing) {
			(void) sprintf(stack, "\tstack(%d);\n", depth);
		} else {
			(void) sprintf(stack, ", stack(%d)", depth);
		}
	} else {
		(void) sprintf(stack, "");
	}

	if (info->ev_acquire != NULL) {
		/*
		 * If this is a hold event, we need to generate an additional
		 * clause for the acquire; the clause for the release will be
		 * generated with the aggregating statement, below.
		 */
		dprog_add("%s\n", info->ev_acquire);
		predicate_add(&pred, info->ev_predicate, NULL, 0);
		predicate_add(&pred, g_predicate, NULL, 0);
		if (pred != NULL)
			dprog_add("/%s/\n", pred);

		dprog_add("{\n");
		(void) sprintf(buf, "self->ev%d[(uintptr_t)arg0]", event);

		if (info->ev_type == 'H') {
			dprog_add("\t%s = timestamp;\n", buf);
		} else {
			/*
			 * If this isn't a hold event, it's the recursive
			 * error event.  For this, we simply bump the
			 * thread-local, per-lock count.
			 */
			dprog_add("\t%s++;\n", buf);
		}

		dprog_add("}\n\n");
		predicate_destroy(&pred);
		pred = NULL;

		if (info->ev_type == 'E') {
			/*
			 * If this is the recursive lock error event, we need
			 * to generate an additional clause to decrement the
			 * thread-local, per-lock count.  This assures that we
			 * only execute the aggregating clause if we have
			 * recursive entry.
			 */
			dprog_add("%s\n", info->ev_name);
			dprog_add("/%s/\n{\n\t%s--;\n}\n\n", buf, buf);
		}

		predicate_add(&pred, buf, NULL, 0);

		if (info->ev_type == 'H') {
			(void) sprintf(buf, "timestamp -\n\t    "
			    "self->ev%d[(uintptr_t)arg0]", event);
		}

		arg1 = buf;
	} else {
		predicate_add(&pred, info->ev_predicate, NULL, 0);
		if (info->ev_type != 'I')
			predicate_add(&pred, g_predicate, NULL, 0);
		else
			predicate_add(&pred, g_ipredicate, NULL, 0);
	}

	if ((dur = g_min_duration[event]) != 0)
		predicate_add(&pred, arg1, ">=", dur);

	dprog_add("%s\n", info->ev_name);

	if (pred != NULL)
		dprog_add("/%s/\n", pred);
	predicate_destroy(&pred);

	dprog_add("{\n");

	if (g_tracing) {
		dprog_add("\ttrace(%dULL);\n", event);
		dprog_add("\ttrace(%s);\n", arg0);
		dprog_add("\ttrace(%s);\n", caller);
		dprog_add(stack);
	} else {
		/*
		 * The ordering here is important:  when we process the
		 * aggregate, we count on the fact that @avg appears before
		 * @hist in program order to assure that @avg is assigned the
		 * first aggregation variable ID and @hist assigned the
		 * second; see the comment in process_aggregate() for details.
		 */
		dprog_add("\t@avg[%dULL, %s, %s%s] = avg(%s);\n",
		    event, arg0, caller, stack, arg1);

		if (g_recsize >= LS_HIST) {
			dprog_add("\t@hist[%dULL, %s, %s%s] = quantize"
			    "(%s);\n", event, arg0, caller, stack, arg1);
		}
	}

	if (info->ev_acquire != NULL)
		dprog_add("\tself->ev%d[arg0] = 0;\n", event);

	dprog_add("}\n\n");
}