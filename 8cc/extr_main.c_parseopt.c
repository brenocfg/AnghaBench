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
 int /*<<< orphan*/  add_include_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cppdefs ; 
 int cpponly ; 
 int dontlink ; 
 int dumpasm ; 
 int /*<<< orphan*/  dumpast ; 
 int enable_warning ; 
 int /*<<< orphan*/  error (char*) ; 
 int getopt (int,char**,char*) ; 
 char* infile ; 
 int /*<<< orphan*/  make_buffer () ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 int /*<<< orphan*/  outfile ; 
 int /*<<< orphan*/  parse_f_arg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_m_arg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_warnings_arg (int /*<<< orphan*/ ) ; 
 char* strchr (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  usage (int) ; 

__attribute__((used)) static void parseopt(int argc, char **argv) {
    cppdefs = make_buffer();
    for (;;) {
        int opt = getopt(argc, argv, "I:ED:O:SU:W:acd:f:gm:o:hw");
        if (opt == -1)
            break;
        switch (opt) {
        case 'I': add_include_path(optarg); break;
        case 'E': cpponly = true; break;
        case 'D': {
            char *p = strchr(optarg, '=');
            if (p)
                *p = ' ';
            buf_printf(cppdefs, "#define %s\n", optarg);
            break;
        }
        case 'O': break;
        case 'S': dumpasm = true; break;
        case 'U':
            buf_printf(cppdefs, "#undef %s\n", optarg);
            break;
        case 'W': parse_warnings_arg(optarg); break;
        case 'c': dontlink = true; break;
        case 'f': parse_f_arg(optarg); break;
        case 'm': parse_m_arg(optarg); break;
        case 'g': break;
        case 'o': outfile = optarg; break;
        case 'w': enable_warning = false; break;
        case 'h':
            usage(0);
        default:
            usage(1);
        }
    }
    if (optind != argc - 1)
        usage(1);

    if (!dumpast && !cpponly && !dumpasm && !dontlink)
        error("One of -a, -c, -E or -S must be specified");
    infile = argv[optind];
}