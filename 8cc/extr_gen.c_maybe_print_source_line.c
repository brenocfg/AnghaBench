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
 int /*<<< orphan*/  dumpsource ; 
 int /*<<< orphan*/  emit_nostack (char*,char*) ; 
 char** map_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  map_put (int /*<<< orphan*/ ,char*,char**) ; 
 char** read_source_file (char*) ; 
 int /*<<< orphan*/  source_lines ; 

__attribute__((used)) static void maybe_print_source_line(char *file, int line) {
    if (!dumpsource)
        return;
    char **lines = map_get(source_lines, file);
    if (!lines) {
        lines = read_source_file(file);
        if (!lines)
            return;
        map_put(source_lines, file, lines);
    }
    int len = 0;
    for (char **p = lines; *p; p++)
        len++;
    emit_nostack("# %s", lines[line - 1]);
}