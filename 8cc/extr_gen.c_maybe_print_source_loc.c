#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* sourceLoc; } ;
struct TYPE_4__ {char* file; int /*<<< orphan*/  line; } ;
typedef  TYPE_2__ Node ;

/* Variables and functions */
 int /*<<< orphan*/  emit (char*,...) ; 
 char* format (char*,long,int /*<<< orphan*/ ) ; 
 char* last_loc ; 
 scalar_t__ map_get (int /*<<< orphan*/ ,char*) ; 
 int map_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_put (int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  maybe_print_source_line (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quote_cstring (char*) ; 
 int /*<<< orphan*/  source_files ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void maybe_print_source_loc(Node *node) {
    if (!node->sourceLoc)
        return;
    char *file = node->sourceLoc->file;
    long fileno = (long)map_get(source_files, file);
    if (!fileno) {
        fileno = map_len(source_files) + 1;
        map_put(source_files, file, (void *)fileno);
        emit(".file %ld \"%s\"", fileno, quote_cstring(file));
    }
    char *loc = format(".loc %ld %d 0", fileno, node->sourceLoc->line);
    if (strcmp(loc, last_loc)) {
        emit("%s", loc);
        maybe_print_source_line(file, node->sourceLoc->line);
    }
    last_loc = loc;
}