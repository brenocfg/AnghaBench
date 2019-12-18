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

/* Variables and functions */
 int TOKEN_LIST_SIZE ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  parse_args (int,char**) ; 
 int /*<<< orphan*/  parse_file (char*,int*,char**) ; 
 int /*<<< orphan*/  set_option_defaults () ; 

void do_config(char *file)
{
    extern int __crt0_argc;
    extern char **__crt0_argv;

    /* Our token list */
    int i, argc;
    char *argv[TOKEN_LIST_SIZE];

    set_option_defaults();
    for(i = 0; i < TOKEN_LIST_SIZE; i += 1) argv[i] = NULL;

    /* Check configuration file */
    if(file) parse_file(file, &argc, argv);

    /* Check extracted tokens */
    parse_args(argc, argv);

    /* Free token list */
    for(i = 0; i < argc; i += 1) if(argv[argc]) free (argv[argc]);

    /* Check command line */
    parse_args(__crt0_argc, __crt0_argv);
}