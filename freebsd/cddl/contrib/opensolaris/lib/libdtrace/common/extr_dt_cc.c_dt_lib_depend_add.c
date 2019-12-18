#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
typedef  int /*<<< orphan*/  dt_list_t ;
struct TYPE_7__ {struct TYPE_7__* dtld_libpath; int /*<<< orphan*/ * dtld_library; } ;
typedef  TYPE_1__ dt_lib_depend_t ;

/* Variables and functions */
 int /*<<< orphan*/  EDT_NOMEM ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* dt_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  dt_list_append (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int dt_set_errno (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* dt_zalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 int /*<<< orphan*/  strlcpy (TYPE_1__*,char const*,int) ; 
 char* strrchr (char const*,char) ; 

int
dt_lib_depend_add(dtrace_hdl_t *dtp, dt_list_t *dlp, const char *arg)
{
	dt_lib_depend_t *dld;
	const char *end;

	assert(arg != NULL);

	if ((end = strrchr(arg, '/')) == NULL)
		return (dt_set_errno(dtp, EINVAL));

	if ((dld = dt_zalloc(dtp, sizeof (dt_lib_depend_t))) == NULL)
		return (-1);

	if ((dld->dtld_libpath = dt_alloc(dtp, MAXPATHLEN)) == NULL) {
		dt_free(dtp, dld);
		return (-1);
	}

	(void) strlcpy(dld->dtld_libpath, arg, end - arg + 2);
	if ((dld->dtld_library = strdup(arg)) == NULL) {
		dt_free(dtp, dld->dtld_libpath);
		dt_free(dtp, dld);
		return (dt_set_errno(dtp, EDT_NOMEM));
	}

	dt_list_append(dlp, dld);
	return (0);
}