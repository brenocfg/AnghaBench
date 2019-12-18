#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ from; scalar_t__ to; } ;
typedef  TYPE_1__ substring_t ;
struct pid_namespace {int pid_gid; int hide_pid; } ;

/* Variables and functions */
 int MAX_OPT_ARGS ; 
#define  Opt_gid 129 
#define  Opt_hidepid 128 
 int /*<<< orphan*/  match_int (TYPE_1__*,int*) ; 
 int match_token (char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  tokens ; 

__attribute__((used)) static int proc_parse_options(char *options, struct pid_namespace *pid)
{
	char *p;
	substring_t args[MAX_OPT_ARGS];
	int option;

	if (!options)
		return 1;

	while ((p = strsep(&options, ",")) != NULL) {
		int token;
		if (!*p)
			continue;

		args[0].to = args[0].from = 0;
		token = match_token(p, tokens, args);
		switch (token) {
		case Opt_gid:
			if (match_int(&args[0], &option))
				return 0;
			pid->pid_gid = option;
			break;
		case Opt_hidepid:
			if (match_int(&args[0], &option))
				return 0;
			if (option < 0 || option > 2) {
				pr_err("proc: hidepid value must be between 0 and 2.\n");
				return 0;
			}
			pid->hide_pid = option;
			break;
		default:
			pr_err("proc: unrecognized mount option \"%s\" "
			       "or missing value\n", p);
			return 0;
		}
	}

	return 1;
}