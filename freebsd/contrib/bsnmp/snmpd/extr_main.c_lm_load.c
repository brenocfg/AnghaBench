#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct TYPE_3__ {size_t* subs; int len; } ;
struct lmodule {int flags; struct lmodule* path; int /*<<< orphan*/ * handle; TYPE_2__* config; TYPE_1__ index; int /*<<< orphan*/  section; } ;
struct TYPE_4__ {int (* init ) (struct lmodule*,int,char**) ;} ;

/* Variables and functions */
 scalar_t__ COMM_INITIALIZE ; 
 int /*<<< orphan*/  INSERT_OBJECT_OID (struct lmodule*,int /*<<< orphan*/ *) ; 
 int LM_ONSTARTLIST ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int MAX_MOD_ARGS ; 
 int RTLD_GLOBAL ; 
 int RTLD_NOW ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct lmodule*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct lmodule*,int /*<<< orphan*/ ) ; 
 scalar_t__ community ; 
 int /*<<< orphan*/  dlclose (int /*<<< orphan*/ *) ; 
 int dlerror () ; 
 int /*<<< orphan*/ * dlopen (struct lmodule*,int) ; 
 TYPE_2__* dlsym (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free (struct lmodule*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  lmodules ; 
 struct lmodule* malloc (int) ; 
 int /*<<< orphan*/  modules_start ; 
 int nprogargs ; 
 char** progargs ; 
 int /*<<< orphan*/  start ; 
 struct lmodule* strdup (char const*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,size_t) ; 
 int stub1 (struct lmodule*,int,char**) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 

struct lmodule *
lm_load(const char *path, const char *section)
{
	struct lmodule *m;
	int err;
	int i;
	char *av[MAX_MOD_ARGS + 1];
	int ac;
	u_int u;

	if ((m = malloc(sizeof(*m))) == NULL) {
		syslog(LOG_ERR, "lm_load: %m");
		return (NULL);
	}
	m->handle = NULL;
	m->flags = 0;
	strlcpy(m->section, section, sizeof(m->section));

	if ((m->path = strdup(path)) == NULL) {
		syslog(LOG_ERR, "lm_load: %m");
		goto err;
	}

	/*
	 * Make index
	 */
	m->index.subs[0] = strlen(section);
	m->index.len = m->index.subs[0] + 1;
	for (u = 0; u < m->index.subs[0]; u++)
		m->index.subs[u + 1] = section[u];

	/*
	 * Load the object file and locate the config structure
	 */
	if ((m->handle = dlopen(m->path, RTLD_NOW|RTLD_GLOBAL)) == NULL) {
		syslog(LOG_ERR, "lm_load: open %s", dlerror());
		goto err;
	}

	if ((m->config = dlsym(m->handle, "config")) == NULL) {
		syslog(LOG_ERR, "lm_load: no 'config' symbol %s", dlerror());
		goto err;
	}

	/*
	 * Insert it into the right place
	 */
	INSERT_OBJECT_OID(m, &lmodules);

	/* preserve order */
	if (community == COMM_INITIALIZE) {
		m->flags |= LM_ONSTARTLIST;
		TAILQ_INSERT_TAIL(&modules_start, m, start);
	}

	/*
	 * make the argument vector.
	 */
	ac = 0;
	for (i = 0; i < nprogargs; i++) {
		if (strlen(progargs[i]) >= strlen(section) + 1 &&
		    strncmp(progargs[i], section, strlen(section)) == 0 &&
		    progargs[i][strlen(section)] == ':') {
			if (ac == MAX_MOD_ARGS) {
				syslog(LOG_WARNING, "too many arguments for "
				    "module '%s", section);
				break;
			}
			av[ac++] = &progargs[i][strlen(section)+1];
		}
	}
	av[ac] = NULL;

	/*
	 * Run the initialization function
	 */
	if ((err = (*m->config->init)(m, ac, av)) != 0) {
		syslog(LOG_ERR, "lm_load: init failed: %d", err);
		TAILQ_REMOVE(&lmodules, m, link);
		goto err;
	}

	return (m);

  err:
	if ((m->flags & LM_ONSTARTLIST) != 0)
		TAILQ_REMOVE(&modules_start, m, start);
	if (m->handle)
		dlclose(m->handle);
	free(m->path);
	free(m);
	return (NULL);
}