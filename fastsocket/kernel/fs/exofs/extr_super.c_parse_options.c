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
typedef  int /*<<< orphan*/  substring_t ;
struct exofs_mountopt {int timeout; int /*<<< orphan*/  pid; } ;
typedef  int /*<<< orphan*/  str ;

/* Variables and functions */
 int BLK_DEFAULT_SG_TIMEOUT ; 
 int EINVAL ; 
 int /*<<< orphan*/  EXOFS_DBGMSG (char*,char*) ; 
 int /*<<< orphan*/  EXOFS_ERR (char*,...) ; 
 int /*<<< orphan*/  EXOFS_MIN_PID ; 
 int HZ ; 
 int MAX_OPT_ARGS ; 
#define  Opt_pid 129 
#define  Opt_to 128 
 int /*<<< orphan*/  match_int (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  match_strlcpy (char*,int /*<<< orphan*/ *,int) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct exofs_mountopt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  simple_strtoull (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  tokens ; 

__attribute__((used)) static int parse_options(char *options, struct exofs_mountopt *opts)
{
	char *p;
	substring_t args[MAX_OPT_ARGS];
	int option;
	bool s_pid = false;

	EXOFS_DBGMSG("parse_options %s\n", options);
	/* defaults */
	memset(opts, 0, sizeof(*opts));
	opts->timeout = BLK_DEFAULT_SG_TIMEOUT;

	while ((p = strsep(&options, ",")) != NULL) {
		int token;
		char str[32];

		if (!*p)
			continue;

		token = match_token(p, tokens, args);
		switch (token) {
		case Opt_pid:
			if (0 == match_strlcpy(str, &args[0], sizeof(str)))
				return -EINVAL;
			opts->pid = simple_strtoull(str, NULL, 0);
			if (opts->pid < EXOFS_MIN_PID) {
				EXOFS_ERR("Partition ID must be >= %u",
					  EXOFS_MIN_PID);
				return -EINVAL;
			}
			s_pid = 1;
			break;
		case Opt_to:
			if (match_int(&args[0], &option))
				return -EINVAL;
			if (option <= 0) {
				EXOFS_ERR("Timout must be > 0");
				return -EINVAL;
			}
			opts->timeout = option * HZ;
			break;
		}
	}

	if (!s_pid) {
		EXOFS_ERR("Need to specify the following options:\n");
		EXOFS_ERR("    -o pid=pid_no_to_use\n");
		return -EINVAL;
	}

	return 0;
}