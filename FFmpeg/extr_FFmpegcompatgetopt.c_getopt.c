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
 int EOF ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 char* optarg ; 
 int optind ; 
 int optopt ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int getopt(int argc, char *argv[], char *opts)
{
    static int sp = 1;
    int c;
    char *cp;

    if (sp == 1) {
        if (optind >= argc ||
            argv[optind][0] != '-' || argv[optind][1] == '\0')
            return EOF;
        else if (!strcmp(argv[optind], "--")) {
            optind++;
            return EOF;
        }
    }
    optopt = c = argv[optind][sp];
    if (c == ':' || !(cp = strchr(opts, c))) {
        fprintf(stderr, ": illegal option -- %c\n", c);
        if (argv[optind][++sp] == '\0') {
            optind++;
            sp = 1;
        }
        return '?';
    }
    if (*++cp == ':') {
        if (argv[optind][sp+1] != '\0')
            optarg = &argv[optind++][sp+1];
        else if(++optind >= argc) {
            fprintf(stderr, ": option requires an argument -- %c\n", c);
            sp = 1;
            return '?';
        } else
            optarg = argv[optind++];
        sp = 1;
    } else {
        if (argv[optind][++sp] == '\0') {
            sp = 1;
            optind++;
        }
        optarg = NULL;
    }

    return c;
}