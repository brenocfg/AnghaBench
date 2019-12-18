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
typedef  int uid_t ;
typedef  int /*<<< orphan*/  substring_t ;
typedef  int pid_t ;
typedef  int gid_t ;

/* Variables and functions */
 int AUTOFS_PROTO_VERSION ; 
 int MAX_OPT_ARGS ; 
#define  Opt_fd 133 
#define  Opt_gid 132 
#define  Opt_maxproto 131 
#define  Opt_minproto 130 
#define  Opt_pgrp 129 
#define  Opt_uid 128 
 int /*<<< orphan*/  autofs_tokens ; 
 int /*<<< orphan*/  current ; 
 int current_gid () ; 
 int current_uid () ; 
 int /*<<< orphan*/  match_int (int /*<<< orphan*/ *,int*) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* strsep (char**,char*) ; 
 int task_pgrp_nr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_options(char *options, int *pipefd, uid_t *uid, gid_t *gid,
		pid_t *pgrp, int *minproto, int *maxproto)
{
	char *p;
	substring_t args[MAX_OPT_ARGS];
	int option;

	*uid = current_uid();
	*gid = current_gid();
	*pgrp = task_pgrp_nr(current);

	*minproto = *maxproto = AUTOFS_PROTO_VERSION;

	*pipefd = -1;

	if (!options)
		return 1;

	while ((p = strsep(&options, ",")) != NULL) {
		int token;
		if (!*p)
			continue;

		token = match_token(p, autofs_tokens, args);
		switch (token) {
		case Opt_fd:
			if (match_int(&args[0], &option))
				return 1;
			*pipefd = option;
			break;
		case Opt_uid:
			if (match_int(&args[0], &option))
				return 1;
			*uid = option;
			break;
		case Opt_gid:
			if (match_int(&args[0], &option))
				return 1;
			*gid = option;
			break;
		case Opt_pgrp:
			if (match_int(&args[0], &option))
				return 1;
			*pgrp = option;
			break;
		case Opt_minproto:
			if (match_int(&args[0], &option))
				return 1;
			*minproto = option;
			break;
		case Opt_maxproto:
			if (match_int(&args[0], &option))
				return 1;
			*maxproto = option;
			break;
		default:
			return 1;
		}
	}
	return (*pipefd < 0);
}