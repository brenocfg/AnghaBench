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
 int dumpast ; 
 int dumpsource ; 
 int dumpstack ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage (int) ; 

__attribute__((used)) static void parse_f_arg(char *s) {
    if (!strcmp(s, "dump-ast"))
        dumpast = true;
    else if (!strcmp(s, "dump-stack"))
        dumpstack = true;
    else if (!strcmp(s, "no-dump-source"))
        dumpsource = false;
    else
        usage(1);
}