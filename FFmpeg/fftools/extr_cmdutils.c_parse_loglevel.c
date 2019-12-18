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
typedef  int /*<<< orphan*/  OptionDef ;

/* Variables and functions */
 int /*<<< orphan*/  check_options (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  dump_argument (char*) ; 
 int /*<<< orphan*/  fflush (scalar_t__) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 int /*<<< orphan*/  fputc (char,scalar_t__) ; 
 char* getenv (char*) ; 
 int hide_banner ; 
 int /*<<< orphan*/  init_report (char const*) ; 
 int locate_option (int,char**,int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  opt_loglevel (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ report_file ; 

void parse_loglevel(int argc, char **argv, const OptionDef *options)
{
    int idx = locate_option(argc, argv, options, "loglevel");
    const char *env;

    check_options(options);

    if (!idx)
        idx = locate_option(argc, argv, options, "v");
    if (idx && argv[idx + 1])
        opt_loglevel(NULL, "loglevel", argv[idx + 1]);
    idx = locate_option(argc, argv, options, "report");
    if ((env = getenv("FFREPORT")) || idx) {
        init_report(env);
        if (report_file) {
            int i;
            fprintf(report_file, "Command line:\n");
            for (i = 0; i < argc; i++) {
                dump_argument(argv[i]);
                fputc(i < argc - 1 ? ' ' : '\n', report_file);
            }
            fflush(report_file);
        }
    }
    idx = locate_option(argc, argv, options, "hide_banner");
    if (idx)
        hide_banner = 1;
}