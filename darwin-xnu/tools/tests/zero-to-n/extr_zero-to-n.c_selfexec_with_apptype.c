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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  posix_spawnattr_t ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  POSIX_SPAWN_PROC_TYPE_APP_DEFAULT ; 
 int /*<<< orphan*/  POSIX_SPAWN_SETEXEC ; 
 int _NSGetExecutablePath (char*,int*) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errc (int /*<<< orphan*/ ,int,char*) ; 
 int posix_spawn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**,char**) ; 
 int posix_spawnattr_init (int /*<<< orphan*/ *) ; 
 int posix_spawnattr_setflags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int posix_spawnattr_setprocesstype_np (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
selfexec_with_apptype(int argc, char *argv[])
{
	int ret;
	posix_spawnattr_t attr;
	extern char **environ;
	char *new_argv[argc + 1 + 1 /* NULL */];
	int i;
	char prog[PATH_MAX];
	uint32_t prog_size = PATH_MAX;

	ret = _NSGetExecutablePath(prog, &prog_size);
	if (ret) err(EX_OSERR, "_NSGetExecutablePath");

	for (i=0; i < argc; i++) {
		new_argv[i] = argv[i];
	}

	new_argv[i]   = "--switched_apptype";
	new_argv[i+1] = NULL;

	ret = posix_spawnattr_init(&attr);
	if (ret) errc(EX_OSERR, ret, "posix_spawnattr_init");

	ret = posix_spawnattr_setflags(&attr, POSIX_SPAWN_SETEXEC);
	if (ret) errc(EX_OSERR, ret, "posix_spawnattr_setflags");

	ret = posix_spawnattr_setprocesstype_np(&attr, POSIX_SPAWN_PROC_TYPE_APP_DEFAULT);
	if (ret) errc(EX_OSERR, ret, "posix_spawnattr_setprocesstype_np");

	ret = posix_spawn(NULL, prog, NULL, &attr, new_argv, environ);
	if (ret) errc(EX_OSERR, ret, "posix_spawn");
}