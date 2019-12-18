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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void usage(int exitcode) {
    fprintf(exitcode ? stderr : stdout,
            "Usage: 8cc [ -E ][ -a ] [ -h ] <file>\n\n"
            "\n"
            "  -I<path>          add to include path\n"
            "  -E                print preprocessed source code\n"
            "  -D name           Predefine name as a macro\n"
            "  -D name=def\n"
            "  -S                Stop before assembly (default)\n"
            "  -c                Do not run linker (default)\n"
            "  -U name           Undefine name\n"
            "  -fdump-ast        print AST\n"
            "  -fdump-stack      Print stacktrace\n"
            "  -fno-dump-source  Do not emit source code as assembly comment\n"
            "  -o filename       Output to the specified file\n"
            "  -g                Do nothing at this moment\n"
            "  -Wall             Enable all warnings\n"
            "  -Werror           Make all warnings into errors\n"
            "  -O<number>        Does nothing at this moment\n"
            "  -m64              Output 64-bit code (default)\n"
            "  -w                Disable all warnings\n"
            "  -h                print this help\n"
            "\n"
            "One of -a, -c, -E or -S must be specified.\n\n");
    exit(exitcode);
}