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
struct v9fs_session_info {int afid; int debug; int dfltuid; int dfltgid; int nodev; int /*<<< orphan*/  uid; int /*<<< orphan*/  flags; void* cache; int /*<<< orphan*/ * cachetag; int /*<<< orphan*/  aname; int /*<<< orphan*/  uname; } ;

/* Variables and functions */
 void* CACHE_FSCACHE ; 
 void* CACHE_LOOSE ; 
 void* CACHE_NONE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_OPT_ARGS ; 
#define  Opt_access 139 
#define  Opt_afid 138 
#define  Opt_cache 137 
#define  Opt_cache_loose 136 
#define  Opt_cachetag 135 
#define  Opt_debug 134 
#define  Opt_dfltgid 133 
#define  Opt_dfltuid 132 
#define  Opt_fscache 131 
#define  Opt_nodevmap 130 
#define  Opt_remotename 129 
#define  Opt_uname 128 
 int /*<<< orphan*/  P9_DEBUG_ERROR ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PATH_MAX ; 
 int /*<<< orphan*/  V9FS_ACCESS_ANY ; 
 int /*<<< orphan*/  V9FS_ACCESS_MASK ; 
 int /*<<< orphan*/  V9FS_ACCESS_SINGLE ; 
 int /*<<< orphan*/  V9FS_ACCESS_USER ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 
 int match_int (int /*<<< orphan*/ *,int*) ; 
 void* match_strdup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  match_strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int p9_debug_level ; 
 int /*<<< orphan*/  simple_strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  tokens ; 

__attribute__((used)) static int v9fs_parse_options(struct v9fs_session_info *v9ses, char *opts)
{
	char *options;
	substring_t args[MAX_OPT_ARGS];
	char *p;
	int option = 0;
	char *s, *e;
	int ret = 0;

	/* setup defaults */
	v9ses->afid = ~0;
	v9ses->debug = 0;
	v9ses->cache = 0;
#ifdef CONFIG_9P_FSCACHE
	v9ses->cachetag = NULL;
#endif

	if (!opts)
		return 0;

	options = kstrdup(opts, GFP_KERNEL);
	if (!options)
		goto fail_option_alloc;

	while ((p = strsep(&options, ",")) != NULL) {
		int token;
		if (!*p)
			continue;
		token = match_token(p, tokens, args);
		if (token < Opt_uname) {
			int r = match_int(&args[0], &option);
			if (r < 0) {
				P9_DPRINTK(P9_DEBUG_ERROR,
					"integer field, but no integer?\n");
				ret = r;
				continue;
			}
		}
		switch (token) {
		case Opt_debug:
			v9ses->debug = option;
#ifdef CONFIG_NET_9P_DEBUG
			p9_debug_level = option;
#endif
			break;

		case Opt_dfltuid:
			v9ses->dfltuid = option;
			break;
		case Opt_dfltgid:
			v9ses->dfltgid = option;
			break;
		case Opt_afid:
			v9ses->afid = option;
			break;
		case Opt_uname:
			match_strlcpy(v9ses->uname, &args[0], PATH_MAX);
			break;
		case Opt_remotename:
			match_strlcpy(v9ses->aname, &args[0], PATH_MAX);
			break;
		case Opt_nodevmap:
			v9ses->nodev = 1;
			break;
		case Opt_cache_loose:
			v9ses->cache = CACHE_LOOSE;
			break;
		case Opt_fscache:
			v9ses->cache = CACHE_FSCACHE;
			break;
		case Opt_cachetag:
#ifdef CONFIG_9P_FSCACHE
			v9ses->cachetag = match_strdup(&args[0]);
#endif
			break;
		case Opt_cache:
			s = match_strdup(&args[0]);
			if (!s)
				goto fail_option_alloc;

			if (strcmp(s, "loose") == 0)
				v9ses->cache = CACHE_LOOSE;
			else if (strcmp(s, "fscache") == 0)
				v9ses->cache = CACHE_FSCACHE;
			else
				v9ses->cache = CACHE_NONE;
			kfree(s);
			break;

		case Opt_access:
			s = match_strdup(&args[0]);
			if (!s)
				goto fail_option_alloc;

			v9ses->flags &= ~V9FS_ACCESS_MASK;
			if (strcmp(s, "user") == 0)
				v9ses->flags |= V9FS_ACCESS_USER;
			else if (strcmp(s, "any") == 0)
				v9ses->flags |= V9FS_ACCESS_ANY;
			else {
				v9ses->flags |= V9FS_ACCESS_SINGLE;
				v9ses->uid = simple_strtoul(s, &e, 10);
				if (*e != '\0')
					v9ses->uid = ~0;
			}
			kfree(s);
			break;

		default:
			continue;
		}
	}
	kfree(options);
	return ret;

fail_option_alloc:
	P9_DPRINTK(P9_DEBUG_ERROR,
		   "failed to allocate copy of option argument\n");
	return -ENOMEM;
}