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
typedef  int /*<<< orphan*/  fileargs_t ;
typedef  int /*<<< orphan*/  cap_rights_t ;
struct TYPE_4__ {int /*<<< orphan*/  def_filename; } ;
struct TYPE_3__ {int /*<<< orphan*/ * fileargs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_FSTAT ; 
 int /*<<< orphan*/  CAP_MMAP_R ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  FA_OPEN ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caph_cache_catpages () ; 
 scalar_t__ caph_enter_casper () ; 
 scalar_t__ caph_limit_stdio () ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * fileargs_init (int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__ nm_info ; 
 TYPE_1__ nm_opts ; 
 char* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
enter_cap_mode(int argc, char **argv)
{
	cap_rights_t rights;
	fileargs_t *fa;
	char *defaultfn;

	cap_rights_init(&rights, CAP_FSTAT, CAP_MMAP_R);

	if (argc == 0) {
		defaultfn = strdup(nm_info.def_filename);
		if (defaultfn == NULL)
			err(EXIT_FAILURE, "strdup");
		argc = 1;
		argv = &defaultfn;
	}

	fa = fileargs_init(argc, argv, O_RDONLY, 0, &rights, FA_OPEN);
	if (fa == NULL)
		err(EXIT_FAILURE, "failed to initialize fileargs");

	caph_cache_catpages();
	if (caph_limit_stdio() < 0)
		err(EXIT_FAILURE, "failed to limit stdio rights");
	if (caph_enter_casper() < 0)
		err(EXIT_FAILURE, "failed to enter capability mode");

	nm_opts.fileargs = fa;
}