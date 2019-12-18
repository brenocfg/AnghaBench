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
struct p9_client {int dotu; int msize; int /*<<< orphan*/  trans_mod; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_OPT_ARGS ; 
#define  Opt_legacy 130 
#define  Opt_msize 129 
#define  Opt_trans 128 
 int /*<<< orphan*/  P9_DEBUG_ERROR ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 
 int match_int (int /*<<< orphan*/ *,int*) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  tokens ; 
 int /*<<< orphan*/  v9fs_get_trans_by_name (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_opts(char *opts, struct p9_client *clnt)
{
	char *options;
	char *p;
	substring_t args[MAX_OPT_ARGS];
	int option;
	int ret = 0;

	clnt->dotu = 1;
	clnt->msize = 8192;

	if (!opts)
		return 0;

	options = kstrdup(opts, GFP_KERNEL);
	if (!options) {
		P9_DPRINTK(P9_DEBUG_ERROR,
				"failed to allocate copy of option string\n");
		return -ENOMEM;
	}

	while ((p = strsep(&options, ",")) != NULL) {
		int token;
		if (!*p)
			continue;
		token = match_token(p, tokens, args);
		if (token < Opt_trans) {
			int r = match_int(&args[0], &option);
			if (r < 0) {
				P9_DPRINTK(P9_DEBUG_ERROR,
					"integer field, but no integer?\n");
				ret = r;
				continue;
			}
		}
		switch (token) {
		case Opt_msize:
			clnt->msize = option;
			break;
		case Opt_trans:
			clnt->trans_mod = v9fs_get_trans_by_name(&args[0]);
			break;
		case Opt_legacy:
			clnt->dotu = 0;
			break;
		default:
			continue;
		}
	}

	kfree(options);
	return ret;
}