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
struct trace_probe {TYPE_1__* args; int /*<<< orphan*/  nr_args; } ;
struct TYPE_3__ {int name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct trace_probe*) ; 
 char* KPROBE_EVENT_SYSTEM ; 
 int MAX_EVENT_NAME_LEN ; 
 int MAX_TRACE_ARGS ; 
 int PTR_ERR (struct trace_probe*) ; 
 struct trace_probe* alloc_trace_probe (char*,char*,void*,char*,unsigned long,int,int) ; 
 scalar_t__ conflict_field_name (int,TYPE_1__*,int) ; 
 struct trace_probe* find_trace_probe (char*,char*) ; 
 int /*<<< orphan*/  free_trace_probe (struct trace_probe*) ; 
 int /*<<< orphan*/  is_good_name (int) ; 
 scalar_t__ isdigit (char) ; 
 void* kstrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int parse_probe_arg (char*,struct trace_probe*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  probe_lock ; 
 int register_trace_probe (struct trace_probe*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,...) ; 
 int split_symbol_offset (char*,unsigned long*) ; 
 char* strchr (char*,char) ; 
 int strict_strtoul (char*,int /*<<< orphan*/ ,unsigned long*) ; 
 scalar_t__ strlen (char*) ; 
 int unregister_trace_probe (struct trace_probe*) ; 

__attribute__((used)) static int create_trace_probe(int argc, char **argv)
{
	/*
	 * Argument syntax:
	 *  - Add kprobe: p[:[GRP/]EVENT] KSYM[+OFFS]|KADDR [FETCHARGS]
	 *  - Add kretprobe: r[:[GRP/]EVENT] KSYM[+0] [FETCHARGS]
	 * Fetch args:
	 *  $retval	: fetch return value
	 *  $stack	: fetch stack address
	 *  $stackN	: fetch Nth of stack (N:0-)
	 *  @ADDR	: fetch memory at ADDR (ADDR should be in kernel)
	 *  @SYM[+|-offs] : fetch memory at SYM +|- offs (SYM is a data symbol)
	 *  %REG	: fetch register REG
	 * Dereferencing memory fetch:
	 *  +|-offs(ARG) : fetch memory at ARG +|- offs address.
	 * Alias name of args:
	 *  NAME=FETCHARG : set NAME as alias of FETCHARG.
	 * Type of args:
	 *  FETCHARG:TYPE : use TYPE instead of unsigned long.
	 */
	struct trace_probe *tp;
	int i, ret = 0;
	bool is_return = false, is_delete = false;
	char *symbol = NULL, *event = NULL, *group = NULL;
	char *arg;
	unsigned long offset = 0;
	void *addr = NULL;
	char buf[MAX_EVENT_NAME_LEN];

	/* argc must be >= 1 */
	if (argv[0][0] == 'p')
		is_return = false;
	else if (argv[0][0] == 'r')
		is_return = true;
	else if (argv[0][0] == '-')
		is_delete = true;
	else {
		pr_info("Probe definition must be started with 'p', 'r' or"
			" '-'.\n");
		return -EINVAL;
	}

	if (argv[0][1] == ':') {
		event = &argv[0][2];
		if (strchr(event, '/')) {
			group = event;
			event = strchr(group, '/') + 1;
			event[-1] = '\0';
			if (strlen(group) == 0) {
				pr_info("Group name is not specified\n");
				return -EINVAL;
			}
		}
		if (strlen(event) == 0) {
			pr_info("Event name is not specified\n");
			return -EINVAL;
		}
	}
	if (!group)
		group = KPROBE_EVENT_SYSTEM;

	if (is_delete) {
		if (!event) {
			pr_info("Delete command needs an event name.\n");
			return -EINVAL;
		}
		mutex_lock(&probe_lock);
		tp = find_trace_probe(event, group);
		if (!tp) {
			mutex_unlock(&probe_lock);
			pr_info("Event %s/%s doesn't exist.\n", group, event);
			return -ENOENT;
		}
		/* delete an event */
		ret = unregister_trace_probe(tp);
		if (ret == 0)
			free_trace_probe(tp);
		mutex_unlock(&probe_lock);
		return ret;
	}

	if (argc < 2) {
		pr_info("Probe point is not specified.\n");
		return -EINVAL;
	}
	if (isdigit(argv[1][0])) {
		if (is_return) {
			pr_info("Return probe point must be a symbol.\n");
			return -EINVAL;
		}
		/* an address specified */
		ret = strict_strtoul(&argv[1][0], 0, (unsigned long *)&addr);
		if (ret) {
			pr_info("Failed to parse address.\n");
			return ret;
		}
	} else {
		/* a symbol specified */
		symbol = argv[1];
		/* TODO: support .init module functions */
		ret = split_symbol_offset(symbol, &offset);
		if (ret) {
			pr_info("Failed to parse symbol.\n");
			return ret;
		}
		if (offset && is_return) {
			pr_info("Return probe must be used without offset.\n");
			return -EINVAL;
		}
	}
	argc -= 2; argv += 2;

	/* setup a probe */
	if (!event) {
		/* Make a new event name */
		if (symbol)
			snprintf(buf, MAX_EVENT_NAME_LEN, "%c_%s_%ld",
				 is_return ? 'r' : 'p', symbol, offset);
		else
			snprintf(buf, MAX_EVENT_NAME_LEN, "%c_0x%p",
				 is_return ? 'r' : 'p', addr);
		event = buf;
	}
	tp = alloc_trace_probe(group, event, addr, symbol, offset, argc,
			       is_return);
	if (IS_ERR(tp)) {
		pr_info("Failed to allocate trace_probe.(%d)\n",
			(int)PTR_ERR(tp));
		return PTR_ERR(tp);
	}

	/* parse arguments */
	ret = 0;
	for (i = 0; i < argc && i < MAX_TRACE_ARGS; i++) {
		/* Increment count for freeing args in error case */
		tp->nr_args++;

		/* Parse argument name */
		arg = strchr(argv[i], '=');
		if (arg) {
			*arg++ = '\0';
			tp->args[i].name = kstrdup(argv[i], GFP_KERNEL);
		} else {
			arg = argv[i];
			/* If argument name is omitted, set "argN" */
			snprintf(buf, MAX_EVENT_NAME_LEN, "arg%d", i + 1);
			tp->args[i].name = kstrdup(buf, GFP_KERNEL);
		}

		if (!tp->args[i].name) {
			pr_info("Failed to allocate argument[%d] name.\n", i);
			ret = -ENOMEM;
			goto error;
		}

		if (!is_good_name(tp->args[i].name)) {
			pr_info("Invalid argument[%d] name: %s\n",
				i, tp->args[i].name);
			ret = -EINVAL;
			goto error;
		}

		if (conflict_field_name(tp->args[i].name, tp->args, i)) {
			pr_info("Argument[%d] name '%s' conflicts with "
				"another field.\n", i, argv[i]);
			ret = -EINVAL;
			goto error;
		}

		/* Parse fetch argument */
		ret = parse_probe_arg(arg, tp, &tp->args[i], is_return);
		if (ret) {
			pr_info("Parse error at argument[%d]. (%d)\n", i, ret);
			goto error;
		}
	}

	ret = register_trace_probe(tp);
	if (ret)
		goto error;
	return 0;

error:
	free_trace_probe(tp);
	return ret;
}